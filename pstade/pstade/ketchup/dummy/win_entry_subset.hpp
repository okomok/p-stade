#pragma once

#include "./alt_msg_map_entry_set.hpp"
#include "./begin_msg_map_entry_set.hpp"
#include "./chain_msg_map_entry_set.hpp"
#include "./forwarding_and_reflection_entry_set.hpp"

namespace pstade { namespace ketchup {


struct win_entry_subset :
	alt_msg_map_entry_set,
	begin_msg_map_entry_set,
	chain_msg_map_entry_set,
	forwarding_and_reflection_entry_set
{ };

} } // namespace pstade::ketchup
