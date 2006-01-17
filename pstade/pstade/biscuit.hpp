#pragma once

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(BOOST_MSVC)
	// inline aggressively
	#pragma inline_recursion(on) // turn on inline recursion
	#pragma inline_depth(255) // max inline depth
#endif


///////////////////////////////////////////////////////////////////////////////
// PStade.Biscuit
//
#include "./biscuit/action.hpp"
#include "./biscuit/algorithm.hpp"
#include "./biscuit/match_results.hpp"
#include "./biscuit/parser.hpp"
#include "./biscuit/range.hpp"
#include "./biscuit/state.hpp"
