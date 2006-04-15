#ifndef PSTADE_KETCHUP_CORE_ENTRY_SET_HPP
#define PSTADE_KETCHUP_CORE_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../cmd_ui/cmd_ui.hpp"
#include "../cmd_ui/dependent_value.hpp"
#include "../cmd_ui/entry_set.hpp"
#include "../crack/entry_set.hpp"
#include "../crack/handled_value.hpp"
#include "../frame/entry_set.hpp"
#include "../helper/entry_set.hpp"
#include "../win/entry_set.hpp"
#include "../winx/entry_set.hpp"


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
	typedef ketchup::not_handled not_handled;
	typedef ketchup::cmd_ui cmd_ui;
	typedef ketchup::dependent dependent;
	typedef ketchup::independent independent;
};


} } // namespace pstade::ketchup


#endif
