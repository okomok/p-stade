#ifndef PSTADE_GRAVY_WINDOW_PTR_HPP
#define PSTADE_GRAVY_WINDOW_PTR_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/handle_ptr.hpp"
#include "./detail/is_window.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    typedef
        detail::handle_ptr<HWND, detail::op_is_window>
    window_ptr;


} } // namespace pstade::gravy


#endif
