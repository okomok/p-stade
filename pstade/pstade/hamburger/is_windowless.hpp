#ifndef PSTADE_HAMBURGER_IS_WINDOWLESS_HPP
#define PSTADE_HAMBURGER_IS_WINDOWLESS_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./element.hpp"


namespace pstade { namespace hamburger {


inline
bool is_windowless(const element& elem)
{
    return !elem.window();
}


} } // namespace pstade::hamburger


#endif
