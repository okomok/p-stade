#ifndef PSTADE_TOMATO_WINDOW_IS_OBJECT_OF_HPP
#define PSTADE_TOMATO_WINDOW_IS_OBJECT_OF_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/equals.hpp>
#include "../c_str.hpp"
#include "./class_name.hpp"


namespace pstade { namespace tomato {


template< class CStringizable > inline
bool is_object_of(window_ref wnd, CStringizable const& className)
{
    return oven::equals(tomato::class_name(wnd), tomato::c_str(className));
}


} } // namespace pstade::tomato


#endif
