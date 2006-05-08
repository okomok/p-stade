#ifndef PSTADE_HAMBURGER_VIEW_HPP
#define PSTADE_HAMBURGER_VIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // min, max
#include <stdexcept> // runtime_error
#include <boost/assert.hpp>
#include <boost/microsoft/atl/win.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/frame.hpp> // CMessageFilter, CIdleHandler
#include <pstade/ketchup.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/idle_handler.hpp>
#include <pstade/tomato/message_filter.hpp>
#include <pstade/tomato/window/create_result.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./detail/remove_caption.hpp"
#include "./detail/send_mouse_message.hpp"
#include "./detail/update_layout.hpp"
#include "./dimension.hpp"
#include "./element.hpp"
#include "./rectangle.hpp"
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


    inline
    rectangle initial_rect(element_node& nd)
    {
        try {
            int left      = pstade::lexical(nd.att(Name_left));
            int width     = pstade::lexical(nd.att(Name_width));
            int top       = pstade::lexical(nd.att(Name_top));
            int height    = pstade::lexical(nd.att(Name_height));
            int maxWidth  = pstade::lexical(nd.att(Name_maxWidth));
            int maxHeight = pstade::lexical(nd.att(Name_maxHeight));

            rectangle rc(
                left, top,
                // Workaround: min/max macro
                left + (std::min)(width, maxWidth), top + (std::min)(height, maxHeight)
            );

            if (!rc.IsRectEmpty())
                return rc;
        }
        catch (std::runtime_error& )
        {
        }

        return ATL::CWindow::rcDefault;
    }


} // namespace view_detail


struct view :
    ketchup::message_processor<view,
        view_detail::impl<view>::type,
        element
    >,
    tomato::message_filter<view>,
    tomato::idle_handler<view>
{
private:
    typedef view_detail::impl<view>::type impl_t;

public:
    explicit view()
    {
        hamburger::set_default_view_attributes(*this);
    }

protected:
    void impl_create()
    {
        BOOST_ASSERT(!diet::valid(m_hWnd));

        rectangle rc(view_detail::initial_rect(*this));
        Create(NULL, rc);

        detail::remove_caption(m_hWnd);

        start_message_filter();
        start_idle_handler();

        ShowWindow(SW_NORMAL);
    }

    HWND impl_window()
    {
        BOOST_ASSERT(diet::valid(m_hWnd));

        return m_hWnd;
    }

private:
friend class tomato::access;
    bool on_idle()
    {
        return false;
    }

    bool pre_translate_message(MSG& msg)
    {
        pstade::unused(msg);
        return false;
    }

friend class ketchup::access;
    LRESULT on_create(LPCREATESTRUCT lpCreateStruct)
    {
        pstade::unused(lpCreateStruct);
        return tomato::create_success;
    }

    void on_size(UINT uType, dimension sz)
    {
        if (uType == SIZE_MINIMIZED)
            return;

        detail::update_layout(*this, sz);
    }

    LRESULT on_mouse_message(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return detail::send_mouse_message(*this, uMsg, wParam, lParam, bHandled);
    }

    begin_msg_map
    <
        msg_wm_create<&_::on_create, not_handled>,
        msg_wm_size<&_::on_size>,
        message_handler<WM_MOUSEMOVE, &_::on_mouse_message>
    >
    end_msg_map;
};


namespace view_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<view>("view");
    )


} // namespace view_detail


} } // namespace pstade::hamburger


#endif
