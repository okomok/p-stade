#ifndef PSTADE_OVEN_MAP_KEY_RANGE_HPP
#define PSTADE_OVEN_MAP_KEY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./first_range.hpp"


namespace pstade { namespace oven {


PSTADE_EGG_FUNCTION(make_map_key_range, first_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(map_keys, first_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
