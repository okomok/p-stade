#ifndef PSTADE_TOMATO_WINDOW_IS_PARENT_OF_HPP
#define PSTADE_TOMATO_WINDOW_IS_PARENT_OF_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// ::IsChild


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
bool is_parent_of(HWND hWndParent, HWND hWndChild)
{
	BOOST_ASSERT(diet::valid(hWndParent));
	BOOST_ASSERT(diet::valid(hWndChild));
	
	return hWndParent == ::GetParent(hWndChild);
}


} } // namespace pstade::tomato


#endif
