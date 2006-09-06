#ifndef PSTADE_HAMBURGER_INVALIDATE_HPP
#define PSTADE_HAMBURGER_INVALIDATE_HPP


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
#include "./point.hpp" // origin
#include "./rectangle.hpp"
#include "./size.hpp"


namespace pstade { namespace hamburger {


inline
void invalidate(element& elem, rectangle rc)
{
    boost::optional<HWND> wnd = elem.window();
    if (wnd) {
        ::InvalidateRect(*wnd, rc, FALSE);
        return;
    }

    boost::optional<element&> pa = elem.parent();
    BOOST_ASSERT(pa);

    rc += hamburger::location(elem);
    hamburger::invalidate(*pa, rc);
}


inline
void invalidate(element& elem)
{
    rectangle rc(origin, hamburger::size(elem));
    hamburger::invalidate(elem, rc);
}


} } // namespace pstade::hamburger


#endif
