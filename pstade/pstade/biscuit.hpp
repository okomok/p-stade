#ifndef PSTADE_BISCUIT_HPP
#define PSTADE_BISCUIT_HPP


// PStade.Biscuit Parser Library
//
// Copyright 2006 MB.
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


#include "./biscuit/action.hpp"
#include "./biscuit/algorithm.hpp"
#include "./biscuit/match_results.hpp"
#include "./biscuit/parser.hpp"
#include "./biscuit/range.hpp"
#include "./biscuit/state.hpp"


#endif
