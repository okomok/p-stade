#ifndef PSTADE_HAMBURGER_SET_LOCATION_HPP
#define PSTADE_HAMBURGER_SET_LOCATION_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lexical_cast.hpp>
#include "./element_attributes.hpp"
#include "./point.hpp"


namespace pstade { namespace hamburger {


template< class Element >
point set_location(Element& elem, point pt)
{
    elem%Name_left = pstade::lexical(pt.x);
    elem%Name_top  = pstade::lexical(pt.y);
    detail::invalidate_parent(elem);
}


} } // namespace pstade::hamburger


#endif
