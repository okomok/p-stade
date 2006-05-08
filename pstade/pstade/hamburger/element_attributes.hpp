#ifndef PSTADE_HAMBURGER_ELEMENT_ATTRIBUTES_HPP
#define PSTADE_HAMBURGER_ELEMENT_ATTRIBUTES_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/oven/joint_range.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const ustring, Name_accName,                ("accName"))
PSTADE_INSTANCE(const ustring, Name_accDescription,         ("accDescription"))
PSTADE_INSTANCE(const ustring, Name_accKeyboardShortcut,    ("accKeyboardShortcut"))
PSTADE_INSTANCE(const ustring, Name_alphaBlend,             ("alphaBlend"))
PSTADE_INSTANCE(const ustring, Name_clippingColor,          ("clippingColor"))
PSTADE_INSTANCE(const ustring, Name_clippingImage,          ("clippingImage"))
PSTADE_INSTANCE(const ustring, Name_elementType,            ("elementType"))
PSTADE_INSTANCE(const ustring, Name_enabled,                ("enabled"))
PSTADE_INSTANCE(const ustring, Name_height,                 ("height"))
PSTADE_INSTANCE(const ustring, Name_horizontalAlignment,    ("horizontalAlignment"))
PSTADE_INSTANCE(const ustring, Name_id,                     ("id"))
PSTADE_INSTANCE(const ustring, Name_left,                   ("left"))
PSTADE_INSTANCE(const ustring, Name_passThrough,            ("passThrough"))
PSTADE_INSTANCE(const ustring, Name_tabStop,                ("tabStop"))
PSTADE_INSTANCE(const ustring, Name_top,                    ("top"))
PSTADE_INSTANCE(const ustring, Name_verticalAlignment,      ("verticalAlignment"))
PSTADE_INSTANCE(const ustring, Name_visible,                ("visible"))
PSTADE_INSTANCE(const ustring, Name_width,                  ("width"))
PSTADE_INSTANCE(const ustring, Name_zIndex,                 ("zIndex"))


PSTADE_INSTANCE(const ustring, Value_true,      ("true"))
PSTADE_INSTANCE(const ustring, Value_false,     ("false"))
PSTADE_INSTANCE(const ustring, Value_auto,      ("auto"))
PSTADE_INSTANCE(const ustring, Value_left,      ("left"))
PSTADE_INSTANCE(const ustring, Value_top,       ("top"))
PSTADE_INSTANCE(const ustring, Value_right,     ("right"))
PSTADE_INSTANCE(const ustring, Value_bottom,    ("bottom"))
PSTADE_INSTANCE(const ustring, Value_center,    ("center"))
PSTADE_INSTANCE(const ustring, Value_stretch,   ("stretch"))
PSTADE_INSTANCE(const ustring, Value_zero,      ("0"))


template< class Node >
void set_default_element_attributes(Node& nd)
{
    nd.att(Name_alphaBlend)         = "255";
    nd.att(Name_clippingColor)      = Value_auto;
    nd.att(Name_enabled)            = Value_true;
    nd.att(Name_height)             = Value_zero;
    nd.att(Name_horizontalAlignment)= Value_left;
    nd.att(Name_left)               = Value_zero;
    nd.att(Name_passThrough)        = Value_false;
    nd.att(Name_tabStop)            = Value_true;
    nd.att(Name_top)                = Value_zero;
    nd.att(Name_verticalAlignment)  = Value_top;
    nd.att(Name_visible)            = Value_true;
    nd.att(Name_width)              = Value_zero;
    nd.att(Name_zIndex)             = Value_zero;
}


template< class Node >
void set_default_element_dependent_attributes(Node& nd)
{
    nd.att(Name_elementType)        = nd.name();
    nd.att(Name_id)                 = ustring("unnamed_")|oven::jointed(nd.name());
    nd.att(Name_accName)            = nd.att(Name_id);
}


} } // namespace pstade::hamburger


#endif
