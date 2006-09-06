#ifndef PSTADE_KETCHUP_WINX_ENTRY_SUBSET_HPP
#define PSTADE_KETCHUP_WINX_ENTRY_SUBSET_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./chain_commands_entry_set.hpp"
#include "./wtl_reflection_entry_set.hpp"


namespace pstade { namespace ketchup {


struct winx_entry_subset :
    chain_commands_entry_set,
    wtl_reflection_entry_set
{ };


} } // namespace pstade::ketchup


#endif
