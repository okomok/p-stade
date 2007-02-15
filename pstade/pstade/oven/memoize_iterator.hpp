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
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include "./detail/indexed_deque.hpp"
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class Iterator, class IsRecursive >
struct memoize_iterator;


template< class Iterator >
struct single_pass_data :
    private boost::noncopyable
{
    typedef typename
        boost::iterator_value<Iterator>::type
    value_t;

    typedef
        detail::indexed_deque<value_t>
    table_t;

    typedef typename
        table_t::index_type
    index_type;

    explicit single_pass_data(Iterator const& it) :
        m_base(it)
    { }

    bool is_in_table(index_type const& i) const
    {
        return m_table.is_in_range(i);
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
        m_table.positive_push(dereference());
        ++m_base;
        m_ovalue.reset();
    }

    void decrement()
    {
        m_table.negative_push(dereference());
        --m_base;
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


namespace memoize_iterator_detail {


    template< class Iterator >
    struct traversal
    {
        typedef typename
            detail::pure_traversal<Iterator>::type
        trv_t;

        typedef typename
            boost::mpl::eval_if<
                boost::mpl::not_<
                    boost::is_convertible<trv_t, boost::forward_traversal_tag>
                >,
                boost::mpl::identity<boost::forward_traversal_tag>,
                boost::detail::minimum_category<trv_t, boost::bidirectional_traversal_tag>
            >::type
        type;
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
                typename traversal<Iterator>::type,
                value_t const&,
                typename boost::iterator_difference<Iterator>::type
            >
        type;
    };


    // In a recursive range, 'Iterator' must live outside
    // of the range in order to avoid reference-cycles.
    template< class Data, class IsRecursive >
    struct pointer_of :
        boost::mpl::if_< IsRecursive,
            Data *,
            boost::shared_ptr<Data>
        >
    { };


} // namespace memoize_iterator_detail


template< class Iterator, class IsRecursive = boost::mpl::false_ >
struct memoize_iterator :
    memoize_iterator_detail::super_<Iterator, IsRecursive>::type
{
private:
    typedef typename memoize_iterator_detail::super_<Iterator, IsRecursive>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef single_pass_data<Iterator> data_t;
    typedef typename memoize_iterator_detail::pointer_of<data_t, IsRecursive>::type pdata_t;

public:
    explicit memoize_iterator()
    { }

template< class, class > friend struct memoize_iterator;
    explicit memoize_iterator(pdata_t const& pdata) :
        m_pdata(pdata), m_index(0)
    { }

// as adaptor
    typedef Iterator base_type;

    Iterator const& base() const
    {
        return m_pdata->base();
    }

private:
    pdata_t m_pdata;
    typename data_t::index_type m_index;

    bool is_in_table() const
    {
        return m_pdata->is_in_table(m_index);
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (is_in_table())
            return m_pdata->table(m_index);
        else
            return m_pdata->dereference();
    }

    template< class Other >
    bool equal(Other const& other) const
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
            m_pdata->increment();
            ++m_index;
        }
    }

    void decrement()
    {
        if (is_in_table()) {
            --m_index;
        }
        else {
            m_pdata->decrement();
            --m_index;
        }
    }
};


} } // namespace pstade::oven


#endif
