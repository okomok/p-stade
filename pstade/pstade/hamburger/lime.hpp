#ifndef PSTADE_HAMBURGER_LIME_HPP
#define PSTADE_HAMBURGER_LIME_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lime/ustring.hpp>
#include "./factory.hpp"


namespace pstade { namespace hamburger {


inline // lime customization
element_node *pstade_lime_new_node(element_node& parent, lime::ustring childName)
{
    return hamburger::create_node(parent, childName);
}


} } // namespace pstade::hamburger


#endif
