#ifndef PSTADE_HAMBURGER_POINT_HPP
#define PSTADE_HAMBURGER_POINT_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/wtl/misc.hpp> // CPoint
#include <pstade/instance.hpp>


namespace pstade { namespace hamburger {


    typedef WTL::CPoint
    point;


    PSTADE_INSTANCE(point const, origin, (0)(0))


} } // namespace pstade::hamburger


#endif
