#ifndef PSTADE_OVEN_MAP_KEY_RANGE_HPP
#define PSTADE_OVEN_MAP_KEY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include "./first_range.hpp"


namespace pstade { namespace oven {


typedef make_first_range_fun make_map_key_range_fun;
PSTADE_SINGLETON_CONST(make_map_key_range_fun, make_map_key_range)
PSTADE_PIPABLE(map_keys, make_map_key_range_fun)


} } // namespace pstade::oven


#endif
