#ifndef PSTADE_HAMBURGER_VIEW_ATTRIBUTES_HPP
#define PSTADE_HAMBURGER_VIEW_ATTRIBUTES_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const ustring, Name_backgroundColor,            ("backgroundColor"))
PSTADE_INSTANCE(const ustring, Name_backgroundImage,            ("backgroundImage"))
PSTADE_INSTANCE(const ustring, Name_backgroundImageHueShift,    ("backgroundImageHueShift"))
PSTADE_INSTANCE(const ustring, Name_backgroundImageSaturation,  ("backgroundImageSaturation"))
PSTADE_INSTANCE(const ustring, Name_backgroundTiled,            ("backgroundTile"))
PSTADE_INSTANCE(const ustring, Name_category,                   ("category"))
PSTADE_INSTANCE(const ustring, Name_focusObjectID,              ("focusObjectID"))
PSTADE_INSTANCE(const ustring, Name_maxHeight,                  ("maxHeight"))
PSTADE_INSTANCE(const ustring, Name_maxWidth,                   ("maxWidth"))
PSTADE_INSTANCE(const ustring, Name_minHeight,                  ("minHeight"))
PSTADE_INSTANCE(const ustring, Name_minWidth,                   ("minWidth"))
PSTADE_INSTANCE(const ustring, Name_resizable,                  ("resizable"))
PSTADE_INSTANCE(const ustring, Name_resizeBackgroundImage,      ("resizeBackgroundImage"))
PSTADE_INSTANCE(const ustring, Name_scriptFile,                 ("scriptFile"))
PSTADE_INSTANCE(const ustring, Name_timerInterval,              ("timerInterval"))
PSTADE_INSTANCE(const ustring, Name_title,                      ("title"))
PSTADE_INSTANCE(const ustring, Name_titleBar,                   ("titleBar"))
PSTADE_INSTANCE(const ustring, Name_transparencyColor,          ("transparencyColor"))


PSTADE_INSTANCE(const ustring, Value_none,  ("none"))
PSTADE_INSTANCE(const ustring, Value_white, ("white"))


PSTADE_INSTANCE(const ustring, Value_All,   ("All"))
PSTADE_INSTANCE(const ustring, Value_Radio, ("Radio"))
PSTADE_INSTANCE(const ustring, Value_CD,    ("CD"))
PSTADE_INSTANCE(const ustring, Value_DVD,   ("DVD"))
PSTADE_INSTANCE(const ustring, Value_Music, ("Music"))
PSTADE_INSTANCE(const ustring, Value_Video, ("Video"))


template< class Node >
void set_default_view_attributes(Node& nd)
{
    nd.att(Name_backgroundColor)            = Value_white;
    nd.att(Name_backgroundImageHueShift)    = "0.0";
    nd.att(Name_backgroundImageSaturation)  = "1.0";
    nd.att(Name_backgroundTiled)            = Value_false;
    nd.att(Name_category)                   = Value_All;
    nd.att(Name_maxHeight)                  = Value_zero;
    nd.att(Name_maxWidth)                   = Value_zero;
    nd.att(Name_minHeight)                  = Value_zero;
    nd.att(Name_minWidth)                   = Value_zero;
    nd.att(Name_resizeBackgroundImage)      = Value_false;
    nd.att(Name_timerInterval)              = "1000";
    nd.att(Name_titleBar)                   = Value_true;
}


} } // namespace pstade::hamburger


#endif
