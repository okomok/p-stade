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


PSTADE_INSTANCE(const lime::ustring, view_name, ("view"))

PSTADE_INSTANCE(const lime::ustring, n_backgroundColor,           ("backgroundColor"))
PSTADE_INSTANCE(const lime::ustring, n_backgroundImage,           ("backgroundImage"))
PSTADE_INSTANCE(const lime::ustring, n_backgroundImageHueShift,   ("backgroundImageHueShift"))
PSTADE_INSTANCE(const lime::ustring, n_backgroundImageSaturation, ("backgroundImageSaturation"))
PSTADE_INSTANCE(const lime::ustring, n_backgroundTiled,           ("backgroundTile"))
PSTADE_INSTANCE(const lime::ustring, n_category,                  ("category"))
PSTADE_INSTANCE(const lime::ustring, n_focusObjectID,             ("focusObjectID"))
PSTADE_INSTANCE(const lime::ustring, n_maxHeight,                 ("maxHeight"))
PSTADE_INSTANCE(const lime::ustring, n_maxWidth,                  ("maxWidth"))
PSTADE_INSTANCE(const lime::ustring, n_minHeight,                 ("minHeight"))
PSTADE_INSTANCE(const lime::ustring, n_minWidth,                  ("minWidth"))
PSTADE_INSTANCE(const lime::ustring, n_resizable,                 ("resizable"))
PSTADE_INSTANCE(const lime::ustring, n_resizeBackgroundImage,     ("resizeBackgroundImage"))
PSTADE_INSTANCE(const lime::ustring, n_scriptFile,                ("scriptFile"))
PSTADE_INSTANCE(const lime::ustring, n_timerInterval,             ("timerInterval"))
PSTADE_INSTANCE(const lime::ustring, n_title,                     ("title"))
PSTADE_INSTANCE(const lime::ustring, n_titleBar,                  ("titleBar"))
PSTADE_INSTANCE(const lime::ustring, n_transparencyColor,         ("transparencyColor"))

PSTADE_INSTANCE(const lime::ustring, v_none,    ("none"))
PSTADE_INSTANCE(const lime::ustring, v_white,   ("white"))

PSTADE_INSTANCE(const lime::ustring, v_All,     ("All"))
PSTADE_INSTANCE(const lime::ustring, v_Radio,   ("Radio"))
PSTADE_INSTANCE(const lime::ustring, n_CD,      ("CD"))
PSTADE_INSTANCE(const lime::ustring, n_DVD,     ("DVD"))
PSTADE_INSTANCE(const lime::ustring, n_Music,   ("Music"))
PSTADE_INSTANCE(const lime::ustring, n_Video,   ("Video"))


namespace view_detail {


    template< class ViewT >
    struct super_
    {
        typedef ATL::CWindowImpl<
            ViewT,
            ATL::CWindow,
            ATL::CWinTraits<
                WS_OVERLAPPED|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                WS_EX_APPWINDOW
            >
        > wnd_t;

        typedef ketchup::message_processor<ViewT,
            wnd_t
        > type;
    };


} // namespace view_detail


struct view :
    element,
    view_detail::super_<view>::type,
    WTL::CMessageFilter, WTL::CIdleHandler
{
public:
    // structors
    //
    explicit view(element_node& parent) :
        element(parent, view_name)
    {
        set_default_values();
        WTL::CRect rc(CW_USEDEFAULT, 0, 0, 0);
        Create(NULL, rc, 0, 0, 0);
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
        empty_entry<>
    >
    end_msg_map;

protected:
    // element_interface
    //
    virtual void set_visible_impl(bool )
    { }

private:
    void set_default_values()
    {
        att(n_backgroundColor)              = v_white;
        att(n_backgroundImageHueShift)      = "0.0";
        att(n_backgroundImageSaturation)    = "1.0";
        att(n_backgroundTiled)              = v_false;
        att(n_category)                     = v_All;
        att(n_maxHeight)                    = v_zero;
        att(n_maxWidth)                     = v_zero;
        att(n_minHeight)                    = v_zero;
        att(n_minWidth)                     = v_zero;
        att(n_resizeBackgroundImage)        = v_false;
        att(n_timerInterval)                = "1000";
        att(n_titleBar)                     = v_true;
    }
};


namespace view_detail { namespace {
    

    entry_type entry = hamburger::register_node<view>(view_name);
    

} } // namespace view_detail::unnamed


} } // namespace pstade::hamburger


#endif
