#ifndef PSTADE_TOMATO_MENU_IS_MENU_HPP
#define PSTADE_TOMATO_MENU_IS_MENU_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/instance.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


struct is_menu_fun
{
    bool operator()(HMENU hMenu) const
    {
        pstade::for_debug();
        return ::IsMenu(hMenu)|booleanized;
    }
};


PSTADE_INSTANCE(is_menu_fun const, is_menu, value)


} } // namespace pstade::tomato


#endif
