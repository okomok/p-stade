#ifndef PSTADE_KETCHUP_CMD_UI_ENTRY_SET_HPP
#define PSTADE_KETCHUP_CMD_UI_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/unused.hpp>
#include "./cmd_ui.hpp"
#include "./entry_subset.hpp"
#include "./update_cmd_ui_message.hpp"


namespace pstade { namespace ketchup {


template< class Derived >
struct cmd_ui_entry_set :
    cmd_ui_entry_subset
{
    #include "./detail/handler_entry_set.ipp"
};


} } // namespace pstade::ketchup


#endif
