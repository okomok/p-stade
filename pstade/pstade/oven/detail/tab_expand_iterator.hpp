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


#if !defined(PSTADE_OVEN_DEBUG)
    #define PSTADE_OVEN_DEBUG_SPACE_CH ' '
    #define PSTADE_OVEN_DEBUG_TAB_CH '\t'
#else
    #define PSTADE_OVEN_DEBUG_SPACE_CH 'S'
    #define PSTADE_OVEN_DEBUG_TAB_CH 'T'
#endif


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
            boost::forward_traversal_tag
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

    tab_expand_iterator(ForwardIter it, diff_t tabsize) :
        super_t(it), m_tabsize(tabsize),
        m_space_counter(0), m_diff_from_sol(0),
        m_space_ch(PSTADE_OVEN_DEBUG_SPACE_CH)
    { }

template< class > friend struct tab_expand_iterator;
    template< class F >
    tab_expand_iterator(tab_expand_iterator<F> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_tabsize(other.tabsize()),
        m_space_counter(other.m_space_counter), m_diff_from_sol(other.m_diff_from_sol), 
        m_space_ch(other.space_ch())
    { }

public:
    diff_t tabsize() const
    {
        return m_tabsize;
    }

    diff_t space_ch() const
    {
        return m_space_ch;
    }

private:
    diff_t m_tabsize;
    diff_t m_space_counter;
    diff_t m_diff_from_sol; // from 'start of line'
    mutable val_t m_space_ch;

    bool is_tab() const
    {
        return PSTADE_OVEN_DEBUG_TAB_CH == read(this->base());
    }

    bool is_newline() const
    {
        return '\n' == read(this->base());
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_tabsize == other.m_tabsize && m_space_ch == other.m_space_ch;
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
            return m_space_ch;

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

        bool nl = is_newline();

        ++this->base_reference();
        ++m_diff_from_sol;

        if (nl)
            m_diff_from_sol = 0;
    }
};


} } } // namespace pstade::oven::detail


#endif
