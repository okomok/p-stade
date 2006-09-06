#ifndef PSTADE_HAMBURGER_HAS_TRANSPARENCY_COLOR_HPP
#define PSTADE_HAMBURGER_HAS_TRANSPARENCY_COLOR_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/rgb.hpp>
#include "./element.hpp"
#include "./element_attributes.hpp"


namespace pstade { namespace hamburger {


inline
bool has_transparency_color(element& elem)
{
    return tomato::rgb(elem%Name_transparencyColor);
}


} } // namespace pstade::hamburger


#endif
