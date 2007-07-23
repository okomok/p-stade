#ifndef PSTADE_OVEN_NUMERIC_HPP
#define PSTADE_OVEN_NUMERIC_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/seq/for_each.hpp>
#include <pstade/adl_barrier.hpp>
#include "./detail/lambda_numeric.hpp"
#include "./detail/range_based_ll.hpp"


namespace pstade { namespace oven {


#define PSTADE_numeric \
    (accumulate)(inner_product)(partial_sum)(adjacent_difference) \
/**/


PSTADE_ADL_BARRIER(numeric) {
    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_RANGE_BASED1_LL, ~, PSTADE_numeric)
}


#undef  PSTADE_numeric


} } // namespace pstade::oven


#endif
