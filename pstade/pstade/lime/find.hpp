#ifndef PSTADE_LIME_FIND_HPP
#define PSTADE_LIME_FIND_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include "./node.hpp"


namespace pstade { namespace lime {


template< class Interface >
node<Interface>&
find_root(node<Interface>& child)
{
    boost::optional< node<Interface>& > parent = child.parent();

    if (!parent)
        return child;
    else
        return lime::find_root(parent);
}


template< class Interface, class UnaryPred >
boost::optional< node<Interface>& >
find_child(node<Interface>& parent, UnaryPred pred)
{
    typedef boost::optional< node<Interface>& > opt_t;

    BOOST_FOREACH (node<Interface>& child, parent) {
        if (pred(child))
            return opt_t(child);
    }

    return opt_t();
}


} } // namespace pstade::lime


#endif
