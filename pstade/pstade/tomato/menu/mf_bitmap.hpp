#ifndef PSTADE_TOMATO_MENU_SET_MENU_MF_BITMAP_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_MF_BITMAP_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wce400/STANDARDSDK/Mfc/Src/wceimpl.h


#include <boost/microsoft/sdk/windows.hpp>
#include "../meta/uint.hpp"


namespace pstade { namespace tomato {


struct mf_bitmap :
#if !defined(_WIN32_WCE)
	uint<MF_BITMAP>
#else
	uint<0x00000004L>
#endif
{ };


} } // namespace pstade::tomato


#endif
