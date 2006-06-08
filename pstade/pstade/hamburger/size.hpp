#ifndef PSTADE_HAMBURGER_SIZE_HPP
#define PSTADE_HAMBURGER_SIZE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./element.hpp"
#include "./dimension.hpp"


namespace pstade { namespace hamburger {


inline const
dimension size(const element& elem)
{
    return elem.bounds().Size();
}


} } // namespace pstade::hamburger


#endif
