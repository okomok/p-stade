#ifndef PSTADE_HAMBURGER_HWND_HPP
#define PSTADE_HAMBURGER_HWND_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/window.hpp>
#include "./element.hpp"


namespace pstade { namespace hamburger {


    namespace hwnd_detail {


        inline
        boost::optional<HWND> aux(element& elem)
        {
            boost::optional<HWND> wnd = elem.window();
            if (wnd)
                return *wnd;

            boost::optional<element&> pa = elem.parent();
            BOOST_ASSERT(pa);

            return hwnd_detail::aux(*pa);
        }


    } // namespace hwnd_detail


    inline
    tomato::window hwnd(element& elem)
    {
        boost::optional<HWND> wnd = hwnd_detail::aux(elem);
        return *wnd;
    }


} } // namespace pstade::hamburger


#endif
