#ifndef PSTADE_TOMATO_WINDOW_IS_OBJECT_OF_HPP
#define PSTADE_TOMATO_WINDOW_IS_OBJECT_OF_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include "../diet/valid.hpp"
#include "./class_name.hpp"


namespace pstade { namespace tomato {


inline
bool is_object_of(HWND hWnd, const TCHAR *pszClassName)
{
	BOOST_ASSERT(diet::valid(hWnd));
	BOOST_ASSERT(diet::valid(pszClassName));

	return oven::equals(tomato::class_name(hWnd), pszClassName|oven::null_terminated);
}


} } // namespace pstade::tomato


#endif
