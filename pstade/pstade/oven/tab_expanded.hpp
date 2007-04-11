#ifndef PSTADE_OVEN_TAB_EXPANDED_HPP
#define PSTADE_OVEN_TAB_EXPANDED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


#if !defined(PSTADE_OVEN_DEBUG)
    #define PSTADE_OVEN_DEBUG_SPACE_CH ' '
    #define PSTADE_OVEN_DEBUG_TAB_CH '\t'
#else
    #define PSTADE_OVEN_DEBUG_SPACE_CH 'S'
    #define PSTADE_OVEN_DEBUG_TAB_CH 'T'
#endif


namespace pstade { namespace oven {


namespace tab_expanded_detail {


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

        tab_expand_iterator(ForwardIter const& it, diff_t const& tabsize) :
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
            return *this->base() == PSTADE_OVEN_DEBUG_TAB_CH;
        }

        bool is_newline() const
        {
            return *this->base() == '\n';
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


    template< class Range, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef
            tab_expand_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, diff_t const& tabsize) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return result_type(
                iter_t(boost::begin(rng), tabsize),
                iter_t(boost::end(rng),   tabsize)
            );
        }
    };


} // namespace tab_expanded_detail


PSTADE_FUNCTION(make_tab_expanded, (tab_expanded_detail::baby<_, _>))
PSTADE_PIPABLE(tab_expanded, (op_make_tab_expanded))


} } // namespace pstade::oven


#endif
