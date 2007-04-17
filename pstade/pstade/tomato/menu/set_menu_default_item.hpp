#ifndef PSTADE_TOMATO_MENU_SET_MENU_DEFAULT_ITEM_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_DEFAULT_ITEM_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/unused.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


inline
bool set_menu_default_item(menu_ref menu,
    UINT uItem = static_cast<UINT>(-1),  bool by_position = false)
{
#if !defined(_WIN32_WCE)

    return ::SetMenuDefaultItem(menu, uItem, pstade::copy_construct<UINT>(by_position))|to_boolean;

#else

    pstade::unused(menu, uItem, by_position);
    return true;

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
