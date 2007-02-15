#ifndef PSTADE_OVEN_MEMOIZE_ITERATOR_HPP
#define PSTADE_OVEN_MEMOIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/spirit/iterator/multi_pass.hpp>
//
/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
//
// Differences:
//   No unique-check; rarely unique in range.
//   No end-iterator-check; it seems redundant.


#include <deque>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>


namespace pstade { namespace oven {


template< class Iterator, class IsRecursive >
struct memoize_iterator;


namespace memoize_iterator_detail {


    template< class Iterator >
    struct memo :
        private boost::noncopyable
    {
    private:
        typedef typename boost::iterator_value<Iterator>::type value_t;
        typedef std::deque<value_t> table_t;

    public:
        typedef typename table_t::size_type index_type;

        explicit memo(Iterator const& it) :
            m_base(it)
        { }

        bool is_in_table(index_type const& i) const
        {
            return i != m_table.size();
        }

        value_t const& table(index_type const& i) const
        {
            return m_table[i];
        }

        Iterator const& base() const
        {
            return m_base;
        }

        void increment()
        {
            m_table.push_back(dereference());
            ++m_base;
            m_ovalue.reset();
        }

        value_t const& dereference()
        {
            if (!this->m_ovalue)
                this->m_ovalue = *m_base;

            return *this->m_ovalue;
        }

    private:
        Iterator m_base;
        boost::optional<value_t> m_ovalue; // must be shared to boost the speed!
        table_t m_table;
    };


    template< class Iterator, class IsRecursive >
    struct super_
    {
        typedef typename
            boost::iterator_value<Iterator>::type
        value_t;

        typedef
            boost::iterator_facade<
                memoize_iterator<Iterator, IsRecursive>,
                value_t,
                boost::forward_traversal_tag,
                value_t const&,
                typename boost::iterator_difference<Iterator>::type
            >
        type;
    };


    // In a recursive range, 'Iterator' must live outside
    // of the range in order to avoid reference-cycles.
    template< class Memo, class IsRecursive >
    struct pointer_of :
        boost::mpl::if_< IsRecursive,
            Memo *,
            boost::shared_ptr<Memo>
        >
    { };


} // namespace memoize_iterator_detail


template< class Iterator, class IsRecursive = boost::mpl::false_ >
struct memoize_iterator :
    memoize_iterator_detail::super_<Iterator, IsRecursive>::type
{
private:
    typedef memoize_iterator self_t;
    typedef typename memoize_iterator_detail::super_<Iterator, IsRecursive>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef memoize_iterator_detail::memo<Iterator> memo_t;
    typedef typename memoize_iterator_detail::pointer_of<memo_t, IsRecursive>::type pmemo_t;

public:
    typedef memo_t memo_type;

    explicit memoize_iterator()
    { }

    explicit memoize_iterator(pmemo_t const& pmemo) :
        m_pmemo(pmemo), m_index(0)
    { }

// as adaptor
    typedef Iterator base_type;

    Iterator const& base() const
    {
        return m_pmemo->base();
    }

private:
    pmemo_t m_pmemo;
    typename memo_t::index_type m_index;

    bool is_in_table() const
    {
        return m_pmemo->is_in_table(m_index);
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (is_in_table())
            return m_pmemo->table(m_index);
        else
            return m_pmemo->dereference();
    }

    bool equal(self_t const& other) const
    {
        if (is_in_table() && other.is_in_table())
            return m_index == other.m_index;
        else if (!is_in_table() && !other.is_in_table())
            return base() == other.base();
        else
            return false;
    }

    void increment()
    {
        if (is_in_table()) {
            ++m_index;
        }
        else {
            m_pmemo->increment();
            ++m_index;
        }
    }
};


} } // namespace pstade::oven


#endif
