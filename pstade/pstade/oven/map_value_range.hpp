#ifndef PSTADE_OVEN_MAP_VALUE_RANGE_HPP
#define PSTADE_OVEN_MAP_VALUE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include "./second_range.hpp"


namespace pstade { namespace oven {


typedef op_make_second_range op_make_map_value_range;
PSTADE_SINGLETON_CONST(make_map_value_range, op_make_map_value_range)
PSTADE_PIPABLE(map_values, op_make_map_value_range)


} } // namespace pstade::oven


#endif
