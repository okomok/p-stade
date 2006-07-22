#ifndef PSTADE_OVEN_TAB_EXPAND_ITERATOR_HPP
#define PSTADE_OVEN_TAB_EXPAND_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include "./detail/config.hpp" // DEBUG_SPACE_CH


namespace pstade { namespace oven {


template< class ForwardIter >
struct tab_expand_iterator;


namespace tab_expand_iterator_detail {


    template< class ForwardIter >
    struct super_
    {
        typedef typename boost::iterator_value<ForwardIter>::type val_t;

        typedef boost::iterator_adaptor<
            tab_expand_iterator<ForwardIter>,
            ForwardIter,
            val_t,
            boost::forward_traversal_tag, // sorry
            val_t const
        > type;
    };


} // namespace tab_expand_iterator_detail


template< class ForwardIter >
struct tab_expand_iterator :
    tab_expand_iterator_detail::super_<ForwardIter>::type
{
private:
    typedef tab_expand_iterator self_t;
    typedef typename tab_expand_iterator_detail::super_<ForwardIter>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    tab_expand_iterator()
    { }

    tab_expand_iterator(ForwardIter const& it, int tabsize) :
        super_t(it), m_tabsize(tabsize),
        m_space_counter(0), m_diff_from_sol(0),
        m_space_ch(PSTADE_OVEN_DEBUG_SPACE_CH)
    { }

template< class > friend struct tab_expand_iterator;
    template< class ForwardIter_ >
    tab_expand_iterator(
        tab_expand_iterator<ForwardIter_> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_tabsize(other.tabsize()),
        m_space_counter(other.m_space_counter), m_diff_from_sol(other.m_diff_from_sol), 
        m_space_ch(other.space_ch())
    { }

public:
    diff_t tabsize() const
    { return m_tabsize; }

    diff_t space_ch() const
    { return m_space_ch; }

private:
    diff_t m_tabsize;
    diff_t m_space_counter;
    diff_t m_diff_from_sol; // from 'start of line'
    val_t  m_space_ch;

    bool is_tab() const
    {
        return *this->base() == PSTADE_OVEN_DEBUG_TAB_CH;
    }

    bool is_newline() const
    {
        return *this->base() == '\n';
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

    bool equal(self_t const& other) const
    {
        return
            m_tabsize == other.m_tabsize &&
            this->base() == other.base() &&
            m_space_counter == other.m_space_counter
        ;
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


template< class ForwardIter > inline
tab_expand_iterator<ForwardIter> const
make_tab_expand_iterator(ForwardIter const& it, int tabsize)
{
    return tab_expand_iterator<ForwardIter>(it, tabsize);
}


} } // namespace pstade::oven


#endif
