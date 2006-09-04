#ifndef PSTADE_HAMBURGER_DETAIL_CHAIN_MOUSE_MESSAGE_HPP
#define PSTADE_HAMBURGER_DETAIL_CHAIN_MOUSE_MESSAGE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/reverse_range.hpp>
#include <pstade/oven/sort_range.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/tomato/get.hpp>
#include <pstade/tomato/make.hpp>
#include <pstade/statement.hpp>
#include <pstade/unused.hpp>
#include "../contains.hpp"
#include "../element.hpp"
#include "../location.hpp"
#include "../is_windowless.hpp"
#include "../point.hpp"
#include "../to_parent_to.hpp"
#include "../z_order.hpp"


#include <pstade/instance.hpp>
#include <pstade/napkin/dout.hpp>
#include <pstade/napkin/nout.hpp>
#include <pstade/napkin/ostream.hpp>
#include <pstade/statement.hpp>


namespace pstade { namespace hamburger { namespace detail {


PSTADE_IF_DEBUG (

    PSTADE_INSTANCE(napkin::ostream, mos, (napkin::nout))

    inline
    void show_info(element& elem, point mouse)
    {
        point pt(0, 0);
        pt = to_screen(elem, pt);
        mos << "mouse: " << mouse.x << ',' << mouse.y;
        mos << ", name: " << oven::copy_range<std::string>(elem.name());
        mos << ", id: " << oven::copy_range<std::string>(elem%Name_id);
        mos << ", location: " << location(elem).x << ',' << location(elem).y;
        mos << ", screen: " << pt.x << ',' << pt.y;

        point pt_ = screen_to(elem, mouse);
        mos << ", in_elem: " << pt_.x << ',' << pt_.y << '\n';
    }

)


inline
LRESULT send_mouse_message(bool in_screen,
    element& parent, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT lResult = 0;
    point pt(tomato::get_x(lParam), tomato::get_y(lParam));

    BOOST_FOREACH (
        element& child,
        parent |
            oven::sorted(z_order) |
            oven::reversed )
    {
        // avoid 'oven::filtered' for code size
        if (!hamburger::is_windowless(child))
            continue;

        if (!in_screen) {
            if (!child.bounds().PtInRect(pt))
                continue;
        }
        else {
            // PSTADE_IF_DEBUG( show_info(child, pt); )
            if (!hamburger::contains_in_screen(child, pt))
                continue;
        }

        if (!in_screen)
            pt = hamburger::parent_to(child, pt);

        LPARAM lParam_ = tomato::make_LPARAM(pt.x, pt.y);
        bHandled = child.process_message(NULL, uMsg, wParam, lParam_, lResult);
        if (bHandled)
            break;
    }

    return lResult;
}


inline
bool is_WM_MOUSEMOVE_compatible(UINT uMsg)
{
    return
        uMsg == WM_MOUSEMOVE ||

        uMsg == WM_LBUTTONUP ||
        uMsg == WM_RBUTTONUP ||
        uMsg == WM_MBUTTONUP ||

        uMsg == WM_LBUTTONDOWN ||
        uMsg == WM_RBUTTONDOWN ||
        uMsg == WM_MBUTTONDOWN ||

        uMsg == WM_LBUTTONDBLCLK ||
        uMsg == WM_RBUTTONDBLCLK ||
        uMsg == WM_MBUTTONDBLCLK
    ;
}


inline
bool is_WM_NCHITTEST_compatible(UINT uMsg)
{
    return
        uMsg == WM_NCHITTEST
        // Todo
    ;
}


template< class = void >
struct chain_mouse_message
{
    template< class Derived > static
    bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    {
        BOOL bHandled = FALSE;
        if (detail::is_WM_MOUSEMOVE_compatible(uMsg)) {
            lResult = detail::send_mouse_message(false, derived, uMsg, wParam, lParam, bHandled);
        }
        else if (detail::is_WM_NCHITTEST_compatible(uMsg)) {
            lResult = detail::send_mouse_message(true, derived, uMsg, wParam, lParam, bHandled);
        }

        pstade::unused(hWnd, dwMsgMapID);
        return bHandled|tomato::booleanized;
    }
};


} } } // namespace pstade::hamburger::detail


#endif
