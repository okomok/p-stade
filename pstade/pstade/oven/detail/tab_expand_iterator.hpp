#ifndef PSTADE_OVEN_DETAIL_TAB_EXPAND_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_TAB_EXPAND_ITERATOR_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include "../read.hpp"
#include "./constant_reference.hpp"


namespace pstade { namespace oven { namespace detail {


template< class ForwardIter >
struct tab_expand_iterator;


template< class ForwardIter >
struct tab_expand_iterator_super
{
    typedef
        boost::iterator_adaptor<
            tab_expand_iterator<ForwardIter>,
            ForwardIter,
            boost::use_default,
            boost::forward_traversal_tag,
            typename constant_reference<ForwardIter>::type
        >
    type;
};


template< class ForwardIter >
struct tab_expand_iterator :
    tab_expand_iterator_super<ForwardIter>::type
{
private:
    typedef typename tab_expand_iterator_super<ForwardIter>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    tab_expand_iterator()
    { }

    tab_expand_iterator(ForwardIter it, diff_t tabsize, val_t newline, val_t tab, val_t space) :
        super_t(it), m_tabsize(tabsize),
        m_newline(newline), m_tab(tab), m_space(space),
        m_space_counter(0), m_diff_from_sol(0)
    { }

template< class > friend struct tab_expand_iterator;
    template< class F >
    tab_expand_iterator(tab_expand_iterator<F> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0,
        typename boost::enable_if_convertible<typename tab_expand_iterator<F>::val_t, val_t>::type * = 0
    ) :
        super_t(other.base()), m_tabsize(other.tabsize()),
        m_newline(other.newline()), m_tab(other.tab()), m_space(other.space()),
        m_space_counter(other.m_space_counter), m_diff_from_sol(other.m_diff_from_sol)
    { }

public:
    diff_t tabsize() const
    {
        return m_tabsize;
    }

    val_t newline() const
    {
        return m_newline;
    }

    val_t const& tab() const
    {
        return m_tab;
    }

    val_t const& space() const
    {
        return m_space;
    }

private:
    diff_t m_tabsize;
    val_t m_newline;
    val_t m_tab;
    val_t m_space;
    diff_t m_space_counter;
    diff_t m_diff_from_sol; // from 'start of line'

    bool is_tab() const
    {
        return m_tab == read(this->base());
    }

    bool is_newline() const
    {
        return m_newline == read(this->base());
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_tabsize == other.m_tabsize && m_space == other.m_space;
    }

    // "pseudo space range" functions
    //
    void space_initialize()
    {
        m_space_counter = m_tabsize - m_diff_from_sol % m_tabsize;
    }

    bool space_is_end() const
    {
        return m_space_counter == 0;
    }

    void space_increment()
    {
        --m_space_counter;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!space_is_end() || is_tab())
            return m_space;

        return *this->base();
    }

    template< class F >
    bool equal(tab_expand_iterator<F> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));

        return this->base() == other.base() && m_space_counter == other.m_space_counter;
    }

    void increment()
    {
        if (!space_is_end()) {
            space_increment();
            ++m_diff_from_sol;
            return;
        }

        if (is_tab()) {
            ++this->base_reference(); // see you later

            space_initialize();
            space_increment();
            ++m_diff_from_sol;
            return;
        }

        bool is_nl = is_newline();

        ++this->base_reference();
        ++m_diff_from_sol;

        if (is_nl)
            m_diff_from_sol = 0;
    }
};


} } } // namespace pstade::oven::detail


#endif
