#ifndef PSTADE_HAMBURGER_ELEMENT_ATTRIBUTES_HPP
#define PSTADE_HAMBURGER_ELEMENT_ATTRIBUTES_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// These are thread-safe as far as under VC++ STL.


#include <boost/range/empty.hpp>
#include <pstade/apple/atl/win.hpp>
#include <pstade/instance.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven/joint_range.hpp>
#include <pstade/ustring.hpp>
#include "./rectangle.hpp"


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
void set_default_element_attributes(Node& node)
{
    node%Name_alphaBlend            = "255";
    node%Name_clippingColor         = Value_auto;
    node%Name_enabled               = Value_true;
    node%Name_height                = Value_zero;
    node%Name_horizontalAlignment   = Value_left;
    node%Name_left                  = Value_zero;
    node%Name_passThrough           = Value_false;
    node%Name_tabStop               = Value_true;
    node%Name_top                   = Value_zero;
    node%Name_verticalAlignment     = Value_top;
    node%Name_visible               = Value_true;
    node%Name_width                 = Value_zero;
    node%Name_zIndex                = Value_zero;
}


template< class Node >
void set_default_element_dependent_attributes(Node& node)
{
    if (boost::empty(node%Name_elementType))
        node%Name_elementType = node.name();

    if (boost::empty(node%Name_id))
        node%Name_id = pstade::ustring("unnamed_")|oven::jointed(node.name());

    if (boost::empty(node%Name_accName))
        node%Name_accName  = node%Name_id;
}


} } // namespace pstade::hamburger


#endif
