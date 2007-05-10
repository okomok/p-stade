#ifndef PSTADE_OVEN_MAP_VALUES_HPP
#define PSTADE_OVEN_MAP_VALUES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./elements.hpp"


namespace pstade { namespace oven {


typedef op_make_elements_c<1> op_make_map_values;
PSTADE_CONSTANT(make_map_values, (op_make_map_values))
PSTADE_PIPABLE(map_values, (op_make_map_values))


} } // namespace pstade::oven


#endif
