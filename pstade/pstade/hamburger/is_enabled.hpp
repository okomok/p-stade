#ifndef PSTADE_HAMBURGER_IS_ENABLED_HPP
#define PSTADE_HAMBURGER_IS_ENABLED_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/equals.hpp>
#include "./element_attributes.hpp"


namespace pstade { namespace hamburger {


template< class Node > inline
bool is_enabled(Node& node)
{
    return oven::equals(node%Name_enabled, Value_true);
}


} } // namespace pstade::hamburger


#endif
