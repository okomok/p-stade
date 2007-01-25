#ifndef PSTADE_OVEN_MAP_KEYS_HPP
#define PSTADE_OVEN_MAP_KEYS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./firsts.hpp"


namespace pstade { namespace oven {


typedef op_make_firsts op_make_map_keys;
PSTADE_CONSTANT(make_map_keys, (op_make_map_keys))
PSTADE_PIPABLE(map_keys, (op_make_map_keys))


} } // namespace pstade::oven


#endif
