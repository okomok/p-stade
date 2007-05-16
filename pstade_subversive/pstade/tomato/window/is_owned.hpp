#ifndef PSTADE_TOMATO_WINDOW_IS_OWNED_HPP
#define PSTADE_TOMATO_WINDOW_IS_OWNED_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
bool is_owned(window_ref wnd)
{
    return NULL != ::GetWindow(wnd, GW_OWNER);
}


} } // namespace pstade::tomato


#endif
