#ifndef PSTADE_HAMBURGER_PLACEMENT_HPP
#define PSTADE_HAMBURGER_PLACEMENT_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/ketchup/core.hpp>
#include <pstade/statement.hpp>
#include "./element.hpp"
#include "./factory.hpp"
#include "./rectangle.hpp"
#include "./view_attributes.hpp"


namespace pstade { namespace hamburger {


struct button :
    element
{
protected:
    void impl_create()
    {
        boost::optional<element&> pa = parent();
        if (!pa)
            return;

        int left   = pstade::lexical(*this%Name_left);
        int top    = pstade::lexical(*this%Name_top);
        int width  = pstade::lexical(*this%Name_width);
        int height = pstade::lexical(*this%Name_height);

        rectangle rc(left, top, left+width, top+height);
        pa.set_bounds(rc);
    }
};


namespace button_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<placement>("placement");
    )


} // namespace button_detail


} } // namespace pstade::hamburger


#endif
