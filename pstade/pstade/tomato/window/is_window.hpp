#ifndef PSTADE_TOMATO_WINDOW_IS_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_IS_WINDOW_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/instance.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


struct is_window_fun
{
    bool operator()(HWND hWnd) const
    {
        pstade::for_debug();
        return ::IsWindow(hWnd)|booleanized;
    }
};


PSTADE_INSTANCE(is_window_fun const, is_window, value)


} } // namespace pstade::tomato


#endif
