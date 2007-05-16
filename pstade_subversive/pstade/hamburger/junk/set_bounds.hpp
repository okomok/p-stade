#ifndef PSTADE_HAMBURGER_SET_BOUNDS_HPP
#define PSTADE_HAMBURGER_SET_BOUNDS_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./element.hpp"
#include "./rectangle.hpp"


namespace pstade { namespace hamburger {


inline
void set_bounds(element& elem, rectangle rc)
{
    elem.set_location(rc.TopLeft());
    elem.set_size(rc.Size());
}


} } // namespace pstade::hamburger


#endif
