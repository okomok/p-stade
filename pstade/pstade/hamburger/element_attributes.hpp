#ifndef PSTADE_HAMBURGER_ELEMENT_ATTRIBUTES_HPP
#define PSTADE_HAMBURGER_ELEMENT_ATTRIBUTES_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const ustring, Name_accName,                ("accName"))
PSTADE_INSTANCE(const ustring, Name_accDescription,         ("accDescription"))
PSTADE_INSTANCE(const ustring, Name_accKeyboardShortcut,    ("accKeyboardShortcut"))
PSTADE_INSTANCE(const ustring, Name_alphaBlend,             ("alphaBlend"))
PSTADE_INSTANCE(const ustring, Name_clippingColor,          ("clippingColor"))
PSTADE_INSTANCE(const ustring, Name_clippingImage,          ("clippingImage"))
PSTADE_INSTANCE(const ustring, Name_elementType,            ("elementTyp"))
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


} } // namespace pstade::hamburger


#endif
