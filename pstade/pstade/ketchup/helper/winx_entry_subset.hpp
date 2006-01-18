#pragma once

#include "./chain_commands_entry_set.hpp"
#include "./wtl_reflection_entry_set.hpp"

namespace pstade { namespace ketchup {


struct winx_entry_subset :
	chain_commands_entry_set,
	wtl_reflection_entry_set
{ };


} } // namespace pstade::ketchup
