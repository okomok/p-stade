#ifndef PSTADE_KETCHUP_CORE_ENTRY_SUBSET_HPP
#define PSTADE_KETCHUP_CORE_ENTRY_SUBSET_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../cmd_ui/entry_subset.hpp"
#include "../crack/entry_subset.hpp"
#include "../frame/entry_subset.hpp"
#include "../helper/entry_subset.hpp"
#include "../win/entry_subset.hpp"
#include "../winx/entry_subset.hpp"


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


#endif
