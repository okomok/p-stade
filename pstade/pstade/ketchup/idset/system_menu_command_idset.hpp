#ifndef PSTADE_KETCHUP_IDSET_SYSTEM_MENU_COMMAND_IDSET_HPP
#define PSTADE_KETCHUP_IDSET_SYSTEM_MENU_COMMAND_IDSET_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>


namespace pstade { namespace ketchup {


struct system_menu_command_idset
{
	static bool contains(UINT id)
	{
		return id >= 0xF000 && id < 0xF1F0;
	}
};


} } // namespace pstade::ketchup


#endif
