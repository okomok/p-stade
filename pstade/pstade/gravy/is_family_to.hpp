#ifndef PSTADE_GRAVY_IS_FAMILY_TO_HPP
#define PSTADE_GRAVY_IS_FAMILY_TO_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./toplevel_parent.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    inline
    bool is_family_to(gravy::window_ref wnd1, gravy::window_ref wnd2)
    {
        return toplevel_parent(wnd1) == toplevel_parent(wnd2);
    }


} } // namespace pstade::gravy


#endif
