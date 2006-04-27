#ifndef PSTADE_LIME_NEW_NODE_HPP
#define PSTADE_LIME_NEW_NODE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./node.hpp"
#include "./ustring.hpp"


namespace pstade { namespace lime {


struct default_tag
{ };


namespace new_node_detail {


    inline
    node *pstade_lemon_new_node(ustring name, node& parent, default_tag)
    {
        return new node(name, parent);
    }


} // namespace new_node_detail


template< class DomainTag > inline
node *new_node(ustring name, node& parent)
{
    using namespace new_node_detail;

    return pstade_lemon_new_node(name, parent, DomainTag());
}


} } // namespace pstade::lime


#endif
