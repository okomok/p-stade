#pragma once

#include <pstade/unused.hpp>
#include "./cmd_ui.hpp"
#include "./cmd_ui_entry_subset.hpp"
#include "./update_cmd_ui_message.hpp"

namespace pstade { namespace ketchup {


template< class Derived >
struct cmd_ui_entry_set :
	cmd_ui_entry_subset
{
	#include "./detail/handler_entry_set.ipp"
};


} } // namespace pstade::ketchup
