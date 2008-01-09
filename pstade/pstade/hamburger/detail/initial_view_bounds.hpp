#ifndef PSTADE_HAMBURGER_DETAIL_INITIAL_VIEW_BOUNDS_HPP
#define PSTADE_HAMBURGER_DETAIL_INITIAL_VIEW_BOUNDS_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lexical.hpp>
#include <pstade/tomato/atl/win.hpp> // CWindow
#include "../element_attributes.hpp"
#include "../rectangle.hpp"


namespace pstade { namespace hamburger { namespace detail {


    template< class Node >
    rectangle initial_view_bounds(Node& node)
    {
        try {
            int left    = node%Name_left  |egg::lexical();
            int width   = node%Name_width |egg::lexical();
            int top     = node%Name_top   |egg::lexical();
            int height  = node%Name_height|egg::lexical();

            rectangle rc(
                left, top,
                left + width, top + height
            );

            if (!rc.IsRectEmpty())
                return rc;
        }
        catch (boost::bad_lexical_cast const&) {
        }

        return ATL::CWindow::rcDefault;
    }


} } } // namespace pstade::hamburger::detail


#endif
