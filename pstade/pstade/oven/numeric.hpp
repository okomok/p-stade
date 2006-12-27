#ifndef PSTADE_OVEN_NUMERIC_HPP
#define PSTADE_OVEN_NUMERIC_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <numeric>
#include <pstade/adl_barrier.hpp>
#include <pstade/pass_by.hpp>
#include "./detail/range_based.hpp"


namespace pstade { namespace oven {

PSTADE_ADL_BARRIER(numeric) {


    PSTADE_OVEN_DETAIL_RANGE_BASED(accumulate,          std::accumulate,          (pass_by_value<A0>), (1)(2))
    PSTADE_OVEN_DETAIL_RANGE_BASED(inner_product,       std::inner_product,       (pass_by_value<A1>), (2)(4))
    PSTADE_OVEN_DETAIL_RANGE_BASED(partial_sum,         std::partial_sum,         (pass_by_value<A0>), (1)(2))
    PSTADE_OVEN_DETAIL_RANGE_BASED(adjacent_difference, std::adjacent_difference, (pass_by_value<A0>), (1)(2))


} // ADL barrier

} } // namespace pstade::oven


#endif
