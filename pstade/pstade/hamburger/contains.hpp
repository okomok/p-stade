#ifndef PSTADE_HAMBURGER_CONTAINS_HPP
#define PSTADE_HAMBURGER_CONTAINS_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/boolean_cast.hpp>
#include "./element.hpp"
#include "./point.hpp"
#include "./size.hpp"
#include "./to_screen_to.hpp"


namespace pstade { namespace hamburger {


    inline
    bool contains(const element& elem, point const& in_elem)
    {
        rectangle rc(origin, hamburger::size(elem));
        return rc.PtInRect(in_elem)|gravy::to_boolean;
    }


    inline
    bool contains_in_screen(const element& elem, point const& in_screen)
    {
        point in_elem = hamburger::screen_to(elem, in_screen);
        return hamburger::contains(elem, in_elem);
    }


} } // namespace pstade::hamburger


#endif
