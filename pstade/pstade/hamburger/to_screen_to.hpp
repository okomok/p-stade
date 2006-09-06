#ifndef PSTADE_HAMBURGER_TO_SCREEN_TO_HPP
#define PSTADE_HAMBURGER_TO_SCREEN_TO_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "./element.hpp"
#include "./location.hpp"
#include "./point.hpp" 
#include "./to_parent_to.hpp"


namespace pstade { namespace hamburger {


inline
point to_screen(const element& elem, point in_elem)
{
    boost::optional<HWND> wnd = elem.window();
    if (wnd) {
        ::ClientToScreen(*wnd, &in_elem);
        return in_elem;
    }

    boost::optional<element&> pa = elem.parent();
    BOOST_ASSERT(pa);

    return hamburger::to_screen(*pa, hamburger::to_parent(elem, in_elem));
}


inline
point screen_to(const element& elem, point in_screen)
{
    point origin_in_screen = hamburger::to_screen(elem, origin);
    return in_screen - origin_in_screen;
}


} } // namespace pstade::hamburger


#endif
