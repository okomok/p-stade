#ifndef PSTADE_TOMATO_WINDOW_IS_MDI_CLIENT_AND_CHILD_HPP
#define PSTADE_TOMATO_WINDOW_IS_MDI_CLIENT_AND_CHILD_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./is_owned.hpp"
#include "./is_parent_of.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
bool is_mdi_client_and_child(window_ref mdiClient, window_ref child)
{
    return
        !tomato::is_owned(child) &&
        tomato::is_parent_of(mdiClient, child);
}


} } // namespace pstade::tomato


#endif
