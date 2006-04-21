#ifndef PSTADE_TOMATO_WINDOW_IS_MDI_CLIENT_AND_CHILD_HPP
#define PSTADE_TOMATO_WINDOW_IS_MDI_CLIENT_AND_CHILD_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./is_owned.hpp"
#include "./is_parent_of.hpp"


namespace pstade { namespace tomato {


inline
bool is_mdi_client_and_child(HWND hWndMDIClient, HWND hWndChild)
{
    BOOST_ASSERT(diet::valid(hWndMDIClient));
    BOOST_ASSERT(diet::valid(hWndChild));

    return
        !tomato::is_owned(hWndChild) &&
        tomato::is_parent_of(hWndMDIClient, hWndChild);
}


} } // namespace pstade::tomato


#endif
