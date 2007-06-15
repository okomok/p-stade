#ifndef PSTADE_GRAVY_DETAIL_IS_WINDOW_HPP
#define PSTADE_GRAVY_DETAIL_IS_WINDOW_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/for_debug.hpp>
#include "../boolean_cast.hpp"
#include "../sdk/windows.hpp"


namespace pstade { namespace gravy { namespace detail {


    struct op_is_window
    {
        typedef bool result_type;

        bool operator()(HWND hWnd) const
        {
            for_debug();
            return ::IsWindow(hWnd)|to_boolean;
        }
    };


    PSTADE_CONSTANT(is_window, (op_is_window))


} } } // namespace pstade::gravy::detail


#endif
