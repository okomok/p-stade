#ifndef PSTADE_OVEN_RECURSION_HPP
#define PSTADE_OVEN_RECURSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <limits> // numeric_limits
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/range/begin.hpp>
#include <pstade/function.hpp>
#include <pstade/is_same.hpp>
#include "./begin_end.hpp"
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
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
                boost::single_pass_traversal_tag,
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
        lazy_iterator(Range& rng, op_begin) :
            m_prng(boost::addressof(rng)), m_initialDiff(0)
        { }

        lazy_iterator(Range& rng, op_end) :
            m_prng(boost::addressof(rng)), m_initialDiff((std::numeric_limits<diff_t>::max)())
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
        mutable boost::optional<base_type> m_obase;
        diff_t m_initialDiff;

        void init_base() const
        {
            if (m_obase)
                return;

            m_obase = boost::begin(*m_prng);
            m_obase = detail::next(*m_obase, m_initialDiff);
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return is_same(*m_prng, *other.m_prng);
        }

        bool is_end() const
        {
            return m_initialDiff == (std::numeric_limits<diff_t>::max)();
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(!is_end());

            init_base();
            return *base();
        }

        template< class Other >
        bool equal(Other const& other) const
        {
            BOOST_ASSERT(is_compatible(other));

            if (is_end() != other.is_end())
                return false;

            if (m_obase || other.m_obase)
                return base() == other.base();
            else
                return m_initialDiff == other.m_initialDiff;
        }

        void increment()
        {
            BOOST_ASSERT(!is_end());

            if (m_obase)
                ++*m_obase;
            else
                ++m_initialDiff;
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
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result(iter_t(rng, begin), iter_t(rng, end));
        }
    };


} // recursion_detail


PSTADE_FUNCTION(recursion, (recursion_detail::baby<_>))


} } // namespace pstade::oven


#endif
