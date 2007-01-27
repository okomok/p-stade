#ifndef PSTADE_OVEN_TAB_UNEXPAND_ITERATOR_HPP
#define PSTADE_OVEN_TAB_UNEXPAND_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // advance, distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/object_generator.hpp>
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven {


template< class ForwardIter >
struct tab_unexpand_iterator;


namespace tab_unexpand_iterator_detail {


    template< class ForwardIter >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                tab_unexpand_iterator<ForwardIter>,
                tab_expand_iterator<ForwardIter> // look!
            >
        type;
    };


} // namespace tab_unexpand_iterator_detail


template< class ForwardIter >
struct tab_unexpand_iterator :
    tab_unexpand_iterator_detail::super_<ForwardIter>::type
{
private:
    typedef typename tab_unexpand_iterator_detail::super_<ForwardIter>::type super_t;
    typedef typename super_t::base_type base_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    tab_unexpand_iterator()
    { }

    tab_unexpand_iterator(ForwardIter const& it, ForwardIter const& last, int tabsize) :
        super_t(base_t(it, tabsize)),
        m_last(last, tabsize), m_sol(it, tabsize),
        m_tabsize(tabsize), m_tab_ch(PSTADE_OVEN_DEBUG_TAB_CH)
    { }

template< class > friend struct tab_unexpand_iterator;
    template< class ForwardIter_ >
    tab_unexpand_iterator(
        tab_unexpand_iterator<ForwardIter_> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()),
        m_last(other.end()), m_sol(other.m_sol), 
        m_tabsize(other.tabsize()), m_tab_ch(other.tab_ch())
    { }

public:
    base_t end() const
    {
        return m_last;
    }

    diff_t tabsize() const
    {
        return m_tabsize;
    }

    val_t tab_ch() const
    {
        return m_tab_ch;
    }

private:
    base_t m_last;
    base_t m_sol; // start of line
    diff_t m_tabsize;
    mutable val_t m_tab_ch;

    bool is_newline() const
    {
        return *this->base() == '\n';
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_tabsize == other.m_tabsize && m_tab_ch == other.m_tab_ch;
    }

    diff_t flying_distance() const
    {
        diff_t diff_from_sol = std::distance(m_sol, this->base());
        diff_t diff_required = m_tabsize - diff_from_sol % m_tabsize;
        
        if (diff_required == 1)
            return false; // common sense?
        
        if (diff_required <= space_exploration())
            return diff_required;
        else
            return 0;
    }

    diff_t space_exploration() const
    {
        diff_t spaces = 0;
        for (base_t it = this->base(); it != m_last; ++it) {
            if (*it == PSTADE_OVEN_DEBUG_SPACE_CH)
                ++spaces;
            else
                break;

            if (spaces == m_tabsize) // Apolo 13
                break;
        }

        return spaces;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (flying_distance() != 0)
            return m_tab_ch;

        return *this->base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        diff_t d = flying_distance();
        if (d != 0) {
            std::advance(this->base_reference(), d);
            return;
        }

        bool nl = is_newline();

        ++this->base_reference();

        if (nl)
            m_sol = this->base();
    }
};


PSTADE_OBJECT_GENERATOR(make_tab_unexpand_iterator,
    (tab_unexpand_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
