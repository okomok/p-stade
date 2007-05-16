#ifndef PSTADE_HAMBURGER_SET_SIZE_HPP
#define PSTADE_HAMBURGER_SET_SIZE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lexical_cast.hpp>
#include "./dimension.hpp"
#include "./element_attributes.hpp"


namespace pstade { namespace hamburger {


template< class Element >
void set_size(Element& elem, dimension sz)
{
    if (hamburger::get_size(elem) == sz)
        return;

    elem%Name_width  = pstade::lexical(sz.cx);
    elem%Name_height = pstade::lexical(sz.cy);
    elem.invalidate();
    detail::invalidate_parent(elem);
}


} } // namespace pstade::hamburger


#endif
