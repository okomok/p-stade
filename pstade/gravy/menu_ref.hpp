#ifndef PSTADE_GRAVY_MENU_REF_HPP
#define PSTADE_GRAVY_MENU_REF_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/handle_ref.hpp"
#include "./detail/is_menu.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    typedef
        detail::handle_ref<HMENU, detail::op_is_menu>
    menu_ref;


} } // namespace pstade::gravy


#endif
