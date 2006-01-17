#pragma once

#include "../cmd_ui/cmd_ui_entry_subset.hpp"
#include "../crack/crack_entry_subset.hpp"
#include "../frame/frame_entry_subset.hpp"
#include "../helper/helper_entry_subset.hpp"
#include "../win/win_entry_subset.hpp"
#include "../winx/winx_entry_subset.hpp"

// Note: entry_subset is just a namespace.

namespace pstade { namespace ketchup {


struct entry_subset :
	win_entry_subset,
	crack_entry_subset,
	winx_entry_subset,
	frame_entry_subset,
	cmd_ui_entry_subset,
	helper_entry_subset
{ };


} } // namespace pstade::ketchup
