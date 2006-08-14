#ifndef PSTADE_TOMATO_MENU_SET_MENU_DEFAULT_ITEM_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_DEFAULT_ITEM_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/unused.hpp>
#include "../boolean_cast.hpp"
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
bool set_menu_default_item(HMENU hMenu,
    UINT uItem = static_cast<UINT>(-1),  bool by_position = false)
{
    BOOST_ASSERT(diet::valid(hMenu));

#if !defined(_WIN32_WCE)

    return ::SetMenuDefaultItem(hMenu, uItem, static_cast<UINT>(by_position))|booleanized;

#else

    pstade::unused(hMenu, uItem, by_position);
    return true;

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
