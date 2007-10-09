#ifndef PSTADE_GRAVY_TOPLEVEL_PARENT_HPP
#define PSTADE_GRAVY_TOPLEVEL_PARENT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./sdk/windows.hpp"
#include "./window_ptr.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct T_toplevel_parent
    {
        typedef window_ref result_type;

        window_ref operator()(window_ref wnd) const
        {
            window_ptr pa = ::GetParent(wnd);
            return pa ? (*this)(*pa) : wnd;
        }
    };


    PSTADE_POD_CONSTANT((T_toplevel_parent), toplevel_parent) = {};


} } // namespace pstade::gravy


#endif
