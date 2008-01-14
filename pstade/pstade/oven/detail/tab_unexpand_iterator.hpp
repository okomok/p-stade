#ifndef PSTADE_OVEN_DETAIL_TAB_UNEXPAND_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_TAB_UNEXPAND_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include "../advance_from.hpp"
#include "../iter_range.hpp"
#include "../read.hpp"
#include "./iter_distance.hpp"
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class ForwardIter >
struct tab_unexpand_iterator;


template< class ForwardIter >
struct tab_unexpand_iterator_super
{
    typedef
        boost::iterator_adaptor<
            tab_unexpand_iterator<ForwardIter>,
            tab_expand_iterator<ForwardIter> // look!
        >
    type;
};


template< class ForwardIter >
struct tab_unexpand_iterator :
    tab_unexpand_iterator_super<ForwardIter>::type
{
private:
    typedef typename tab_unexpand_iterator_super<ForwardIter>::type super_t;
    typedef typename super_t::base_type base_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    tab_unexpand_iterator()
    { }

    tab_unexpand_iterator(ForwardIter it, ForwardIter last, diff_t tabsize, val_t newline, val_t tab, val_t space) :
        super_t(base_t(it, tabsize, newline, tab, space)),
        m_last(last, tabsize, newline, tab, space), m_sol(it, tabsize, newline, tab, space)
    { }

template< class > friend struct tab_unexpand_iterator;
    template< class F >
    tab_unexpand_iterator(tab_unexpand_iterator<F> const& other,
        typename boost::enable_if_convertible<typename tab_unexpand_iterator<F>::base_t, base_t>::type * = 0
    ) :
        super_t(other.base()),
        m_last(other.end()), m_sol(other.m_sol)
    { }

public:
    base_t end() const
    {
        return m_last;
    }

    diff_t tabsize() const
    {
        return this->base().tabsize();
    }

    val_t newline() const
    {
        return this->base().newline();
    }

    val_t const& tab() const
    {
        return this->base().tab();
    }

    val_t const& space() const
    {
        return this->base().space();
    }

private:
    base_t m_last;
    base_t m_sol; // start of line

    bool is_newline() const
    {
        return newline() == read(this->base());
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return tabsize() == other.tabsize() && tab() == other.tab();
    }

    diff_t flying_distance() const
    {
        diff_t diff_from_sol = detail::iter_distance(m_sol, this->base());
        diff_t diff_required = tabsize() - diff_from_sol % tabsize();

        if (diff_required == 1)
            return 0; // common sense?

        if (diff_required <= space_exploration())
            return diff_required;
        else
            return 0;
    }

    diff_t space_exploration() const
    {
        diff_t spaces = 0;
        for (base_t it = this->base(); it != m_last; ++it) {
            if (read(it) == space())
                ++spaces;
            else
                break;

            if (spaces == tabsize()) // Apolo 13
                break;
        }

        return spaces;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (flying_distance() != 0)
            return tab();

        return *this->base();
    }

    template< class F >
    bool equal(tab_unexpand_iterator<F> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        diff_t d = flying_distance();
        if (d != 0) {
            this->base_reference() = advance_from(this->base(), d);
            return;
        }

        bool is_nl = is_newline();

        ++this->base_reference();

        if (is_nl)
            m_sol = this->base();
    }
};


} } } // namespace pstade::oven::detail


#endif
