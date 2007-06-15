#ifndef PSTADE_GRAVY_SEND_COMMAND_HPP
#define PSTADE_GRAVY_SEND_COMMAND_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/instance.hpp>
#include "./include/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_send_message
    {
        typedef LRESULT result_type;

        LRESULT operator()(window_ref wnd, UINT msg, WPARAM wParam = 0, LPARAM lParam = 0) const
        {
            return ::SendMessage(wnd, msg, wParam, lParam);
        }
    };


    PSTADE_CONSTANT(send_message, (op_send_message))


} } // namespace pstade::gravy


#endif
