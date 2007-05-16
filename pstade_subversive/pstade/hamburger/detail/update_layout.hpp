#ifndef PSTADE_HAMBURGER_DETAIL_UPDATE_LAYOUT_HPP
#define PSTADE_HAMBURGER_DETAIL_UPDATE_LAYOUT_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include "../dimension.hpp"
#include "../element.hpp"


namespace pstade { namespace hamburger { namespace detail {


inline
void update_layout(element_node& parent, dimension sz)
{
    BOOST_FOREACH (element_node& child, parent) {
        child, parent;
        // ...
    }

    sz;
}


} } } // namespace pstade::hamburger::detail


#endif
