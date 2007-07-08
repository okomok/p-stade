#ifndef PSTADE_OVEN_SIZE_HPP
#define PSTADE_OVEN_SIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The result type is conforming to the latest range proposal.
// For some historical reason, 'boost::size' result type is wrong.


#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./detail/check_nonnegative.hpp"
#include "./range_difference.hpp"


namespace pstade { namespace oven {


namespace size_detail {


    struct baby
    {
        template< class Myself, class Range >
        struct apply :
            range_difference<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            return detail::check_nonnegative(
                boost::end(rng) - boost::begin(rng)
            );
        }
    };


    typedef egg::function<baby> op;


} // namespace size_detail


typedef egg::result_of_auxiliary0<size_detail::op>::type op_size;
PSTADE_ADL_BARRIER(size) { // for 'boost'
    PSTADE_POD_CONSTANT((op_size), size) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({{}}));
}


} } // namespace pstade::oven


#endif
