#ifndef PSTADE_GRAVY_IS_OWNED_HPP
#define PSTADE_GRAVY_IS_OWNED_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct T_is_owned
    {
        typedef bool result_type;

        bool operator()(window_ref wnd) const
        {
            return NULL != ::GetWindow(wnd, GW_OWNER);
        }
    };


    PSTADE_POD_CONSTANT((T_is_owned), is_owned) = {};


} } // namespace pstade::gravy


#endif
