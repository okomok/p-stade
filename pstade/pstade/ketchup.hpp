#ifndef PSTADE_KETCHUP_HPP
#define PSTADE_KETCHUP_HPP


// PStade.Ketchup Message Map Library
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if defined(BOOST_MSVC)
	// inline aggressively
	#pragma inline_recursion(on) // turn on inline recursion
	#pragma inline_depth(255) // max inline depth
#endif


#include "./ketchup/cmd_ui.hpp"
#include "./ketchup/core.hpp"
#include "./ketchup/id.hpp"
#include "./ketchup/idset.hpp"


#endif
