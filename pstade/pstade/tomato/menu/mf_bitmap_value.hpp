#ifndef PSTADE_TOMATO_MENU_SET_MENU_MF_BITMAP_VALUE_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_MF_BITMAP_VALUE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wce400/STANDARDSDK/Mfc/Src/wceimpl.h


#include <boost/mpl/if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "../is_wce.hpp"


namespace pstade { namespace tomato {


struct mf_bitmap :
    boost::mpl::if_< is_wce<>,
        boost::mpl::integral_c<UINT, MF_BITMAP>,
        boost::mpl::integral_c<UINT, 0x00000004L>
    >::type
{ };


} } // namespace pstade::tomato


#endif
