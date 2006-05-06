#ifndef PSTADE_HAMBURGER_VIEW_HPP
#define PSTADE_HAMBURGER_VIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/win.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/frame.hpp> // CMessageFilter, CIdleHandler
#include <pstade/ketchup.hpp>
#include <pstade/tomato/message_loop.hpp>
#include <pstade/tomato/window/create_result.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./element.hpp"
#include "./view_attributes.hpp"


namespace pstade { namespace hamburger {


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
    virtual BOOL OnIdle()
    {
        return FALSE;
    }

    virtual BOOL PreTranslateMessage(MSG *pMsg)
    {
        pstade::unused(pMsg);
        return FALSE; // impl_t::PreTranslateMessage(pMsg);
    }

    // message handlers
    //
    LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        tomato::add_message_filter(this);
        tomato::add_idle_handler(this);

        pstade::unused(lpCreateStruct);
        return tomato::create_success;
    }

    begin_msg_map
    <
        msg_wm_create<&_::OnCreate, not_handled>,
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


namespace view_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<view>("view");
    )


} // namespace view_detail


} } // namespace pstade::hamburger


#endif
