#ifndef PSTADE_TOMATO_WINDOW_WINDOW_PTR_HPP
#define PSTADE_TOMATO_WINDOW_WINDOW_PTR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "../detail/handle_ptr.hpp"
#include "./is_window.hpp"


namespace pstade { namespace tomato {


typedef detail::handle_ptr<HWND, op_is_window>
window_ptr;


} } // namespace pstade::tomato


#endif
