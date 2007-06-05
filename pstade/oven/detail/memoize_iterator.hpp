#ifndef PSTADE_OVEN_DETAIL_MEMOIZE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_MEMOIZE_ITERATOR_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/


// References:
//
// [1] Daniel C. Nuffer, multi_pass iterator, Boost.Spirit, 2001.
//     http://www.boost.org/libs/spirit/doc/multi_pass.html


// Differences from References[1]:
//
// 1. No unique-check; rarely unique in range.
// 2. No end-iterator-check; it seems redundant.


#include <deque>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct memo :
    private boost::noncopyable
{
private:
    typedef typename boost::iterator_value<Iterator>::type value_t;
    typedef std::deque<value_t> table_t;

public:
    typedef typename table_t::size_type index_type;

    explicit memo(Iterator it) :
        m_base(it), m_baseIndex(0)
    { }

    bool is_in_table(index_type i) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(0 <= i && i <= m_baseIndex);
        return i != m_table.size();
    }

    value_t const& deref(index_type i)
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(0 <= i && i <= m_baseIndex);

        if (!is_in_table(i)) {
            BOOST_ASSERT(i == m_baseIndex && m_baseIndex == m_table.size());
            m_table.push_back(*m_base);
        }

        return m_table[i];
    }

    index_type next(index_type i)
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(0 <= i && i <= m_baseIndex);

        if (i == m_baseIndex) {
            if (m_baseIndex == m_table.size())
                    m_table.push_back(*m_base);

            ++m_base;
            ++m_baseIndex;
        }

        return i + 1;
    }

    Iterator base() const
    {
        BOOST_ASSERT(invariant());
        return m_base;
    }

private:
    Iterator m_base;
    index_type m_baseIndex;
    table_t m_table;

    bool invariant() const
    {
        return m_baseIndex == m_table.size() || m_baseIndex + 1 == m_table.size();
    }
};


template< class Iterator, class IsRecursive >
struct memoize_iterator;


// In a recursive range, 'Iterator' must live outside
// of the range in order to avoid reference-cycles.
// Todo: 'xpressive::detail::tracking_ptr' can kick in?
template< class Memo, class IsRecursive >
struct memo_ptr_of :
    boost::mpl::if_< IsRecursive,
        Memo *,
        boost::shared_ptr<Memo>
    >
{ };


template< class Iterator, class IsRecursive >
struct memoize_iterator_super
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


template< class Iterator, class IsRecursive >
struct memoize_iterator :
    memoize_iterator_super<Iterator, IsRecursive>::type
{
private:
    typedef typename memoize_iterator_super<Iterator, IsRecursive>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef memo<Iterator> memo_t;
    typedef typename memo_ptr_of<memo_t, IsRecursive>::type pmemo_t;

public:
    typedef memo_t memo_type;

    explicit memoize_iterator()
    { }

    explicit memoize_iterator(pmemo_t const& pmemo) :
        m_pmemo(pmemo), m_index(0)
    { }

// as adaptor
    typedef Iterator base_type;

    Iterator base() const
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
        return m_pmemo->deref(m_index);
    }

    bool equal(memoize_iterator const& other) const
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
        m_index = m_pmemo->next(m_index);
    }
};


} } } // namespace pstade::oven::detail


#endif
