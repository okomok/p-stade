#ifndef PSTADE_HAMBURGER_UPDATE_HPP
#define PSTADE_HAMBURGER_UPDATE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "./element.hpp"


namespace pstade { namespace hamburger {


inline
void update(element& elem)
{
    boost::optional<HWND> wnd = elem.window();
    if (wnd) {
        ::UpdateWindow(*wnd);
        return;
    }

    boost::optional<element&> pa = elem.parent();
    if (!pa) {
        BOOST_ASSERT(false); // todo
        return;
    }

    hamburger::update(*pa);
}


} } // namespace pstade::hamburger


#endif
