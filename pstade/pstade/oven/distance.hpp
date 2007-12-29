#ifndef PSTADE_OVEN_DISTANCE_HPP
#define PSTADE_OVEN_DISTANCE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./detail/iter_distance.hpp"
#include "./detail/verify_nonnegative.hpp"
#include "./range_difference.hpp"


namespace pstade { namespace oven {


namespace distance_detail {


    struct baby
    {
        template< class Myself, class Range >
        struct apply :
            range_difference<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return detail::verify_nonnegative(
                detail::iter_distance(boost::begin(rng), boost::end(rng))
            );
        }
    };


    typedef egg::function<baby> op;


} // namespace distance_detail


typedef egg::result_of_ambi1<distance_detail::op>::type T_distance;

PSTADE_ADL_BARRIER(distance) { // for 'boost' and 'std'
    PSTADE_POD_CONSTANT((T_distance), distance) = PSTADE_EGG_AMBI({{}});
}


} } // namespace pstade::oven


#endif
