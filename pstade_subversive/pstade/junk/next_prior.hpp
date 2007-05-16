#ifndef PSTADE_OVEN_NEXT_PRIOR_HPP
#define PSTADE_OVEN_NEXT_PRIOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/unused.hpp>
#include "./distance.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace next_prior_detail {


    template< class Range, class Difference > inline
    void check_range(Range& rng, Difference d, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(0 <= d);
        pstade::unused(rng, d);
    }


    template< class Range, class Difference > inline
    void check_range(Range& rng, Difference d, boost::forward_traversal_tag)
    {
        BOOST_ASSERT(0 <= d && d <= oven::distance(rng));
        pstade::unused(rng, d);
    }


    struct baby_next_begin
    {
        template< class Myself, class Range, class Difference = void >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d)
        {
            (check_range)(rng, d, typename range_traversal<Range>::type());
            return boost::next(boost::begin(rng), d);
        }

        template< class Result, class Range >
        Result call(Range& rng)
        {
            (check_range)(rng, 1, typename range_traversal<Range>::type());
            return boost::next(boost::begin(rng));
        }
    };


    struct baby_prior_end
    {
        template< class Myself, class Range, class Difference = void >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d)
        {
            (check_range)(rng, d, typename range_traversal<Range>::type());
            return boost::prior(boost::end(rng), d);
        }

        template< class Result, class Range >
        Result call(Range& rng)
        {
            (check_range)(rng, 1, typename range_traversal<Range>::type());
            return boost::prior(boost::end(rng));
        }
    };


} // namespace next_prior_detail


PSTADE_EGG_FUNCTION(next_begin, next_prior_detail::baby_next_begin)
PSTADE_EGG_FUNCTION(prior_end,  next_prior_detail::baby_prior_end)

PSTADE_EGG_PIPABLE(next_begins, next_prior_detail::baby_next_begin)
PSTADE_EGG_PIPABLE(prior_ends,  next_prior_detail::baby_prior_end)


} } // namespace pstade::oven


#endif
