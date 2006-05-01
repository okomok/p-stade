#ifndef PSTADE_HAMBURGER_VIEW_ATTRIBUTES_HPP
#define PSTADE_HAMBURGER_VIEW_ATTRIBUTES_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/lime/ustring.hpp>


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const lime::ustring, Name_backgroundColor,          ("backgroundColor"))
PSTADE_INSTANCE(const lime::ustring, Name_backgroundImage,          ("backgroundImage"))
PSTADE_INSTANCE(const lime::ustring, Name_backgroundImageHueShift,  ("backgroundImageHueShift"))
PSTADE_INSTANCE(const lime::ustring, Name_backgroundImageSaturation,("backgroundImageSaturation"))
PSTADE_INSTANCE(const lime::ustring, Name_backgroundTiled,          ("backgroundTile"))
PSTADE_INSTANCE(const lime::ustring, Name_category,                 ("category"))
PSTADE_INSTANCE(const lime::ustring, Name_focusObjectID,            ("focusObjectID"))
PSTADE_INSTANCE(const lime::ustring, Name_maxHeight,                ("maxHeight"))
PSTADE_INSTANCE(const lime::ustring, Name_maxWidth,                 ("maxWidth"))
PSTADE_INSTANCE(const lime::ustring, Name_minHeight,                ("minHeight"))
PSTADE_INSTANCE(const lime::ustring, Name_minWidth,                 ("minWidth"))
PSTADE_INSTANCE(const lime::ustring, Name_resizable,                ("resizable"))
PSTADE_INSTANCE(const lime::ustring, Name_resizeBackgroundImage,    ("resizeBackgroundImage"))
PSTADE_INSTANCE(const lime::ustring, Name_scriptFile,               ("scriptFile"))
PSTADE_INSTANCE(const lime::ustring, Name_timerInterval,            ("timerInterval"))
PSTADE_INSTANCE(const lime::ustring, Name_title,                    ("title"))
PSTADE_INSTANCE(const lime::ustring, Name_titleBar,                 ("titleBar"))
PSTADE_INSTANCE(const lime::ustring, Name_transparencyColor,        ("transparencyColor"))


PSTADE_INSTANCE(const lime::ustring, Value_none,    ("none"))
PSTADE_INSTANCE(const lime::ustring, Value_white,   ("white"))


PSTADE_INSTANCE(const lime::ustring, Value_All,     ("All"))
PSTADE_INSTANCE(const lime::ustring, Value_Radio,   ("Radio"))
PSTADE_INSTANCE(const lime::ustring, Value_CD,      ("CD"))
PSTADE_INSTANCE(const lime::ustring, Value_DVD,     ("DVD"))
PSTADE_INSTANCE(const lime::ustring, Value_Music,   ("Music"))
PSTADE_INSTANCE(const lime::ustring, Value_Video,   ("Video"))


} } // namespace pstade::hamburger


#endif
