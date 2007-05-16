#ifndef PSTADE_HAMBURGER_GET_BOUNDS_HPP
#define PSTADE_HAMBURGER_GET_BOUNDS_HPP


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
rectangle get_bounds(const element& elem)
{
    return hamburger::rectangle(elem.get_location(), elem.get_size());
}


} } // namespace pstade::hamburger


#endif
