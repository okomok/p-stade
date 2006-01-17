#pragma once

#include "../cmd_ui/cmd_ui_entry_set.hpp"
#include "../crack/crack_entry_set.hpp"
#include "../frame/frame_entry_set.hpp"
#include "../helper/helper_entry_set.hpp"
#include "../win/win_entry_set.hpp"
#include "../winx/winx_entry_set.hpp"

namespace pstade { namespace ketchup {


template< class Derived >
struct entry_set :
	win_entry_set<Derived>,
	winx_entry_set<Derived>,
	frame_entry_set<Derived>,
	cmd_ui_entry_set<Derived>,
	crack_entry_set<Derived>,
	helper_entry_set<Derived>
{
	typedef Derived _;
};


} } // namespace pstade::ketchup
