#ifndef PSTADE_OVEN_DROPPED_HPP
#define PSTADE_OVEN_DROPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/debug_in_distance.hpp"
#include "./detail/next_prior.hpp" // next
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace dropped_detail {


    template< class Range, class >
    struct baby
    {
        typedef typename
            sub_range_result<Range>::type
        result;

        template< class Difference >
        result call(Range& rng, Difference& d)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            BOOST_ASSERT(detail::debug_in_distance(d, rng));
            return result(detail::next(boost::begin(rng), d), boost::end(rng));
        }
    };


} // namespace dropped_detail


PSTADE_FUNCTION(make_dropped, (dropped_detail::baby<_, _>))
PSTADE_PIPABLE(dropped, (op_make_dropped))


} } // namespace pstade::oven


#endif
