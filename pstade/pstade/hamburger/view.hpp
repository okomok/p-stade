#ifndef PSTADE_HAMBURGER_VIEW_HPP
#define PSTADE_HAMBURGER_VIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/win.hpp>
#include <boost/microsoft/wtl/frame.hpp> // CMessageFilter, CIdleHandler
#include <pstade/ketchup.hpp>
#include <pstade/lime/ustring.hpp>
#include "./element.hpp"


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


namespace view_detail {


    template< class ViewT >
    struct impl
    {
        typedef ATL::CWindowImpl<
            ViewT,
            ATL::CWindow,
            ATL::CWinTraits<
                WS_OVERLAPPED|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                WS_EX_APPWINDOW
            >
        > type;
    };


} // namespace view_detail


struct view :
    ketchup::message_processor<view,
        view_detail::impl<view>::type,
        element
    >,
    WTL::CMessageFilter, WTL::CIdleHandler
{
private:
    typedef view_detail::impl<view>::type impl_t;

public:
    explicit view()
    {
        set_default_values();
    }

    // WTL
    //
    virtual BOOL OnIdle() {
        return FALSE;
    }

    virtual BOOL PreTranslateMessage(MSG* /*pMsg*/) {
        return FALSE;
    }

    begin_msg_map
    <
        empty_entry<>,
        chain_msg_map<impl_t>
    >
    end_msg_map;

private:
    void set_default_values()
    {
        att(Name_backgroundColor)           = Value_white;
        att(Name_backgroundImageHueShift)   = "0.0";
        att(Name_backgroundImageSaturation) = "1.0";
        att(Name_backgroundTiled)           = Value_false;
        att(Name_category)                  = Value_All;
        att(Name_maxHeight)                 = Value_zero;
        att(Name_maxWidth)                  = Value_zero;
        att(Name_minHeight)                 = Value_zero;
        att(Name_minWidth)                  = Value_zero;
        att(Name_resizeBackgroundImage)     = Value_false;
        att(Name_timerInterval)             = "1000";
        att(Name_titleBar)                  = Value_true;
    }
};


namespace view_detail { namespace {
    

    entry_type entry = hamburger::register_node<view>("view");
    

} } // namespace view_detail::unnamed


} } // namespace pstade::hamburger


#endif
