#ifndef PSTADE_TOMATO_WINDOW_IS_OWNED_HPP
#define PSTADE_TOMATO_WINDOW_IS_OWNED_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
bool is_owned(HWND hWnd)
{
    BOOST_ASSERT(diet::valid(hWnd));

    return NULL != ::GetWindow(hWnd, GW_OWNER);
}


} } // namespace pstade::tomato


#endif
