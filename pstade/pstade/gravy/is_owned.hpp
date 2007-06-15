#ifndef PSTADE_GRAVY_IS_OWNED_HPP
#define PSTADE_GRAVY_IS_OWNED_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include "./include/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_is_owned
    {
        typedef bool result_type;

        bool operator()(window_ref wnd) const
        {
            return NULL != ::GetWindow(wnd, GW_OWNER);
        }
    };


    PSTADE_CONSTANT(is_owned, (op_is_owned))


} } // namespace pstade::gravy


#endif
