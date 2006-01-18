#pragma once


namespace pstade { namespace ketchup {


struct system_menu_command_idset
{
	static bool contains(UINT id)
	{
		return id >= 0xF000 && id < 0xF1F0;
	}
};


} } // namespace pstade::ketchup
