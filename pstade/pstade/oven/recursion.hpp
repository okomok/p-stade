#ifndef PSTADE_OVEN_RECURSION_HPP
#define PSTADE_OVEN_RECURSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'lazy_iterator' might be non-conforming.
// The time of the initial dereference never be constant.
// Also, Member functions for RandomAccess were not implemented,
// because the distance of range would be infinite and undefined,
// which is too strange for RandomAccessRange.


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/function.hpp>
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace recursion_detail {


    template< class Range >
    struct lazy_iterator;


    template< class Range >
    struct lazy_iterator_super
    {
        typedef
            boost::iterator_facade<
                lazy_iterator<Range>,
                typename range_value<Range>::type,
                typename boost::detail::minimum_category<
                    boost::bidirectional_traversal_tag,
                    typename range_pure_traversal<Range>::type
                >::type,
                typename range_reference<Range>::type,
                typename range_difference<Range>::type
            >
        type;
    };


    template< class Range >
    struct lazy_iterator :
        lazy_iterator_super<Range>::type
    {
    private:
        typedef typename lazy_iterator_super<Range>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::difference_type diff_t;

    public:
        lazy_iterator()
        { }

    template< class > friend struct lazy_iterator;
        lazy_iterator(Range& rng, bool is_end) :
            m_prng(boost::addressof(rng)), m_is_from_end(is_end), m_saved_diff(0)
        { }

        typedef typename range_iterator<Range>::type base_type;

        base_type const& base() const
        {
            init_base();
            return *m_obase;
        }

        Range& base_range() const
        {
            return *m_prng;
        }

    private:
        Range *m_prng;
        bool m_is_from_end;
        diff_t m_saved_diff;
        mutable boost::optional<base_type> m_obase;

        void init_base() const
        {
            if (m_obase)
                return;

            m_obase = !m_is_from_end ? boost::begin(*m_prng) : boost::end(*m_prng);
            m_obase = detail::next(*m_obase, m_saved_diff);
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            for_debug();
            return m_prng == other.m_prng;
        }

        bool is_maybe_non_end() const
        {
            for_debug();

            if (m_obase) // non-checkable
                return true; 

            return m_is_from_end ? m_saved_diff < 0 : true;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(is_maybe_non_end());

            init_base();
            return *base();
        }

        template< class Other >
        bool equal(Other const& other) const
        {
            BOOST_ASSERT(is_compatible(other));

            // They never meet in infinite range.
            if (m_is_from_end != other.m_is_from_end)
                return false;

            if (m_obase || other.m_obase)
                return base() == other.base();
            else
                return m_saved_diff == other.m_saved_diff;
        }

        void increment()
        {
            BOOST_ASSERT(is_maybe_non_end());

            if (m_obase)
                ++*m_obase;
            else
                ++m_saved_diff;
        }

        void decrement()
        {
            if (m_obase)
                --*m_obase;
            else
                --m_saved_diff;
        }
    };


    template< class Range >
    struct baby
    {
        typedef
            lazy_iterator<Range>
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return result(iter_t(rng, false), iter_t(rng, true));
        }
    };


} // recursion_detail


PSTADE_FUNCTION(recursion, (recursion_detail::baby<_>))


} } // namespace pstade::oven


#endif
