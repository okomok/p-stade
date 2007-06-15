#ifndef PSTADE_GRAVY_SET_MENU_MF_BITMAP_HPP
#define PSTADE_GRAVY_SET_MENU_MF_BITMAP_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wce400/STANDARDSDK/Mfc/Src/wceimpl.h


#include <pstade/static_c.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct mf_bitmap :
#if !defined(_WIN32_WCE)
        static_c<UINT, MF_BITMAP>
#else
        static_c<UINT, 0x00000004L>
#endif
    { };


} } // namespace pstade::gravy


#endif
