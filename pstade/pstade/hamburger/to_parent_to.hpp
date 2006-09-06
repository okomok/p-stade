#ifndef PSTADE_HAMBURGER_TO_PARENT_TO_HPP
#define PSTADE_HAMBURGER_TO_PARENT_TO_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./element.hpp"
#include "./location.hpp"
#include "./point.hpp"


namespace pstade { namespace hamburger {


inline
point to_parent(const element& elem, point in_elem)
{
    return in_elem + hamburger::location(elem);
}


inline
point parent_to(const element& elem, point in_parent)
{
    return in_parent - hamburger::location(elem);
}


} } // namespace pstade::hamburger


#endif
