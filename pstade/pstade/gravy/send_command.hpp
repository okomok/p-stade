#ifndef PSTADE_GRAVY_SEND_COMMAND_HPP
#define PSTADE_GRAVY_SEND_COMMAND_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./sdk/windows.hpp"
#include "./send_message.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_send_command
    {
        typedef BOOL result_type;

        BOOL operator()(window_ref wnd, WORD wID) const
        {
            return send_message(wnd, WM_COMMAND, MAKEWPARAM(wID, 0));
        }
    };


    PSTADE_POD_CONSTANT((op_send_message), send_message) = {};


} } // namespace pstade::gravy


#endif
