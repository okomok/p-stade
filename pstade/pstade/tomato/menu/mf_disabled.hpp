#ifndef PSTADE_TOMATO_MENU_SET_MENU_MF_DISABLED_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_MF_DISABLED_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include "../meta/uint.hpp"


namespace pstade { namespace tomato {


struct mf_disabled :
#if !defined(_WIN32_WCE)
	uint<MF_DISABLED>
#else
	uint<0>
#endif
{ };


} } // namespace pstade::tomato


#endif
