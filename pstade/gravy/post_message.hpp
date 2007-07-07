#ifndef PSTADE_GRAVY_POST_MESSAGE_HPP
#define PSTADE_GRAVY_POST_MESSAGE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/require.hpp>
#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_post_message
    {
        typedef void result_type;

        void operator()(window_ref wnd, UINT msg, WPARAM wParam = 0, LPARAM lParam = 0) const
        {
            PSTADE_REQUIRE(::PostMessage(wnd, msg, wParam, lParam));
        }
    };


    PSTADE_POD_CONSTANT((op_post_message), post_message) = {};


} } // namespace pstade::gravy


#endif
