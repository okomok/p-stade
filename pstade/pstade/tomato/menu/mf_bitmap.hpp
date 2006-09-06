#ifndef PSTADE_TOMATO_MENU_SET_MENU_MF_BITMAP_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_MF_BITMAP_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wce400/STANDARDSDK/Mfc/Src/wceimpl.h


#include <boost/mpl/if.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/static_c.hpp>
#include "../is_wce.hpp"


namespace pstade { namespace tomato {


struct mf_bitmap :
    boost::mpl::if_< is_wce<>,
        static_c<UINT, MF_BITMAP>,
        static_c<UINT, 0x00000004L>
    >::type
{ };


} } // namespace pstade::tomato


#endif
