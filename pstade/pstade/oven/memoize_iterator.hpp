#ifndef PSTADE_OVEN_MEMOIZE_ITERATOR_HPP
#define PSTADE_OVEN_MEMOIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/spirit/iterator/multi_pass.hpp>


#include <deque>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


template< class Iterator, class IsRecursive >
struct memoize_iterator;


namespace memoize_iterator_detail {


    template< class Iterator >
    struct data_super
    {
        typedef typename boost::iterator_value<Iterator>::type value_type;
        typedef std::deque<value_type> table_type;
        typedef typename table_type::size_type index_type;

        bool is_in_table(index_type const& i) const
        {
            return i != m_table.size();
        }

        value_type const& table(index_type const& i) const
        {
            return m_table[i];
        }

    protected:
        boost::optional<value_type> m_ovalue; // must be shared to boost the speed!
        table_type m_table;
    };


    template< class Iterator >
    struct single_pass_data :
        data_super<Iterator>
    {
        typedef data_super<Iterator> super_t;

        explicit single_pass_data(Iterator const& it) :
            m_base(it)
        { }

        Iterator const& base() const
        {
            return m_base;
        }

        void increment()
        {
            this->m_table.push_back(*m_base);
            ++m_base;
            this->m_ovalue.reset();
        }

        typename super_t::value_type const& dereference()
        {
            if (!this->m_ovalue)
                this->m_ovalue = *m_base;

            return *this->m_ovalue;
        }

    private:
        Iterator m_base;
    };


    // In a recursive range, as 'Iterator' must live outside
    // of the range in order to avoid reference-cycles.

    template< class Iterator >
    struct recursive_data :
        data_super<Iterator>
    {
        typedef data_super<Iterator> super_t;

        explicit recursive_data(Iterator *pit) :
            m_pbase(pit)
        { }

        Iterator const& base() const
        {
            return *m_pbase;
        }

        void increment()
        {
            this->m_table.push_back(**m_pbase);
            ++*m_pbase;
            this->m_ovalue.reset();
        }

        typename super_t::value_type const& dereference()
        {
            if (!this->m_ovalue)
                this->m_ovalue = **m_pbase;

            return *this->m_ovalue;
        }

    private:
        Iterator *m_pbase;
    };


    template< class Iterator, class IsRecursive >
    struct data_of :
        boost::mpl::if_< IsRecursive,
            recursive_data<Iterator>,
            single_pass_data<Iterator>
        >
    { };


    template< class Iterator, class IsRecursive >
    struct super_
    {
        typedef typename
            boost::iterator_value<Iterator>::type
        val_t;

        typedef
            boost::iterator_facade<
                memoize_iterator<Iterator, IsRecursive>,
                val_t,
                boost::forward_traversal_tag,
                val_t const&,
                typename boost::iterator_difference<Iterator>::type
            >
        type;
    };


} // namespace memoize_iterator_detail


template< class Iterator, class IsRecursive = boost::mpl::false_ >
struct memoize_iterator :
    memoize_iterator_detail::super_<Iterator, IsRecursive>::type
{
private:
    typedef typename memoize_iterator_detail::super_<Iterator, IsRecursive>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename memoize_iterator_detail::data_of<Iterator, IsRecursive>::type data_t;

public:
    explicit memoize_iterator()
    { }

template< class, class > friend struct memoize_iterator;
    explicit memoize_iterator(Iterator const& it) :
        m_pdata(new data_t(it)),
        m_index(0)
    {
        BOOST_MPL_ASSERT_NOT((IsRecursive));
    }

    explicit memoize_iterator(Iterator *pit) :
        m_pdata(new data_t(pit)),
        m_index(0)
    {
        BOOST_MPL_ASSERT((IsRecursive));
    }

// as adaptor
    typedef Iterator base_type;

    Iterator const& base() const
    {
        return m_pdata->base();
    }

private:
    boost::shared_ptr<data_t> m_pdata;
    typename data_t::index_type m_index;

    bool is_in_table() const
    {
        return m_pdata->is_in_table(m_index);
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (m_pdata->is_in_table(m_index))
            return m_pdata->table(m_index);
        else
            return m_pdata->dereference();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        if (is_in_table() && other.is_in_table())
            return m_index == other.m_index;

        if (!is_in_table() && !other.is_in_table())
            return base() == other.base();

        return false;
    }

    void increment()
    {
        if (is_in_table()) {
            ++m_index;
        }
        else {
            m_pdata->increment();
            ++m_index;
        }
    }
};


PSTADE_OBJECT_GENERATOR(make_memoize_iterator,
    (memoize_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
