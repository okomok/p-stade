#ifndef PSTADE_HAMBURGER_REFRESH_HPP
#define PSTADE_HAMBURGER_REFRESH_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./element.hpp"
#include "./invalidate.hpp"
#include "./update.hpp"


namespace pstade { namespace hamburger {


template< class Element > inline
void refresh(Element& elem)
{
    hamburger::invalidate(elem);
    hamburger::update(elem);
}


} } // namespace pstade::hamburger


#endif
