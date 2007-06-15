#ifndef PSTADE_GRAVY_POST_COMMAND_HPP
#define PSTADE_GRAVY_POST_COMMAND_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include "./include/windows.hpp"
#include "./post_message.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_post_command
    {
        typedef void result_type;

        void operator()(window_ref wnd, WORD wID) const
        {
            return post_message(wnd, WM_COMMAND, MAKEWPARAM(wID, 0));
        }
    };


    PSTADE_CONSTANT(post_command, (op_post_command))


} } // namespace pstade::gravy


#endif
