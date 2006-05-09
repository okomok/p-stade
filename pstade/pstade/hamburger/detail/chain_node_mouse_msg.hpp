#ifndef PSTADE_HAMBURGER_DETAIL_CHAIN_NODE_MOUSE_MSG_HPP
#define PSTADE_HAMBURGER_DETAIL_CHAIN_NODE_MOUSE_MSG_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/oven/reverse_range.hpp>
#include <pstade/oven/filter_range.hpp>
#include <pstade/oven/sort_range.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/tomato/get.hpp>
#include <pstade/tomato/make.hpp>
#include <pstade/unused.hpp>
#include "../element.hpp"
#include "../point.hpp"
#include "./predicates.hpp"


namespace pstade { namespace hamburger { namespace detail {


inline
LRESULT send_WM_MOUSEMOVE_compatible(element_node& parent, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT lResult = 0;
    point pt(tomato::get_x(lParam), tomato::get_y(lParam));

    BOOST_FOREACH (
        element_node& child,
        parent |
            oven::filtered(detail::is_windowless) |
            oven::filtered(detail::in_rectangle(pt)) |
            oven::sorted(detail::z_order) |
            oven::reversed )
    {
        point pt_ = child.get_bounds().TopLeft() - pt;
        LPARAM lParam_ = tomato::make_long(pt_.x, pt_.y);
        bHandled = child.process_message(parent.window(), uMsg, wParam, lParam_, lResult);
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


template< class = void >
struct chain_node_mouse_msg
{
    template< class Derived > static
    bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    {
        BOOL bHandled = FALSE;
        if (detail::is_WM_MOUSEMOVE_compatible(uMsg)) {
            lResult = detail::send_WM_MOUSEMOVE_compatible(derived, uMsg, wParam, lParam, bHandled);
        }

        pstade::unused(hWnd, dwMsgMapID);
        return tomato::boolean(bHandled);
    }
};


} } } // namespace pstade::hamburger::detail


#endif
