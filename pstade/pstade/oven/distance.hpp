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
#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./detail/check_nonnegative.hpp"
#include "./detail/iter_distance.hpp"
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
            return detail::check_nonnegative(
                detail::iter_distance(boost::begin(rng), boost::end(rng))
            );
        }
    };


    typedef egg::function<baby> op;


} // namespace distance_detail


typedef egg::result_of_auxiliary0<distance_detail::op>::type op_distance;

PSTADE_ADL_BARRIER(distance) { // for 'boost' and 'std'
    PSTADE_POD_CONSTANT((op_distance), distance) = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;
}


} } // namespace pstade::oven


#endif
