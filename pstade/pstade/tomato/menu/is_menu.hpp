#ifndef PSTADE_TOMATO_MENU_IS_MENU_HPP
#define PSTADE_TOMATO_MENU_IS_MENU_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/constant.hpp>
#include <pstade/for_debug.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


struct op_is_menu
{
    bool operator()(HMENU hMenu) const
    {
        pstade::for_debug();
        return ::IsMenu(hMenu)|booleanized;
    }
};


PSTADE_CONSTANT(is_menu, op_is_menu)


} } // namespace pstade::tomato


#endif
