#ifndef PSTADE_TOMATO_WINDOW_IS_PARENT_OF_HPP
#define PSTADE_TOMATO_WINDOW_IS_PARENT_OF_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// ::IsChild


#include <pstade/apple/sdk/windows.hpp>
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
bool is_parent_of(window_ref parent, window_ref child)
{
    return parent == ::GetParent(child);
}


} } // namespace pstade::tomato


#endif
