#ifndef PSTADE_HAMBURGER_IS_VISIBLE_HPP
#define PSTADE_HAMBURGER_IS_VISIBLE_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/equals.hpp>
#include "./element_attributes.hpp"


namespace pstade { namespace hamburger {


    template< class Node > inline
    bool is_visible(Node& node)
    {
        return oven::equals(node%Name_visible, Value_true);
    }


} } // namespace pstade::hamburger


#endif
