#ifndef PSTADE_HAMBURGER_SUBVIEW_HPP
#define PSTADE_HAMBURGER_SUBVIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/ketchup.hpp>
#include "./element.hpp"
#include "./view_attributes.hpp"


namespace pstade { namespace hamburger {


struct subview :
    ketchup::message_processor<subview, element>
{
    explicit subview()
    {
        set_default_values();
    }

    begin_msg_map
    <
        empty_entry<>
    >
    end_msg_map;

private:
    void set_default_values()
    {
        att(Name_backgroundColor)               = Value_none;
        att(Name_backgroundImageHueShift)       = "0.0";
        att(Name_backgroundImageSaturation)     = "1.0";
        att(Name_backgroundTiled)               = Value_false;
        att(Name_resizeBackgroundImage)         = Value_false;
    }
};


namespace subview_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_node<subview>("subview");
    )


} // namespace subview_detail


} } // namespace pstade::hamburger


#endif
