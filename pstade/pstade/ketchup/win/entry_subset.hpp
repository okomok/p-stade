#ifndef PSTADE_KETCHUP_WIN_ENTRY_SUBSET_HPP
#define PSTADE_KETCHUP_WIN_ENTRY_SUBSET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
