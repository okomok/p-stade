#ifndef PSTADE_HAMBURGER_DETAIL_SEND_MOUSE_MESSAGE_HPP
#define PSTADE_HAMBURGER_DETAIL_SEND_MOUSE_MESSAGE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/oven/reverse_range.hpp>
#include <pstade/oven/filter_range.hpp>
#include <pstade/tomato/get.hpp>
#include <pstade/tomato/make.hpp>
#include "../element.hpp"
#include "../point.hpp"
#include "./predicates.hpp"
#include "./z_order_range.hpp"


namespace pstade { namespace hamburger { namespace detail {


inline
LRESULT send_mouse_message(element_node& parent, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT lResult = 0;
    point pt(tomato::get_x(lParam), tomato::get_y(lParam));

    BOOST_FOREACH (
        element_node& child,
        parent |
            oven::filtered(detail::is_windowless) |
            oven::filtered(detail::in_rectangle(pt)) |
            z_ordered |
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


} } } // namespace pstade::hamburger::detail


#endif
