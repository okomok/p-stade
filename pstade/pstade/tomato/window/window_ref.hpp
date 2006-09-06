#ifndef PSTADE_TOMATO_WINDOW_WINDOW_REF_HPP
#define PSTADE_TOMATO_WINDOW_WINDOW_REF_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "../detail/handle_ref.hpp"
#include "./is_window.hpp"


namespace pstade { namespace tomato {


typedef detail::handle_ref<HWND, is_window_fun>
window_ref;


} } // namespace pstade::tomato


#endif
