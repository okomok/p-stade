#ifndef PSTADE_LIME_NEW_NODE_HPP
#define PSTADE_LIME_NEW_NODE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <pstade/nullptr.hpp>
#include <pstade/overload.hpp>
#include <pstade/ustring.hpp>
#include "./detail/node_fwd.hpp"


namespace pstade { namespace lime {


namespace new_node_detail {


    template< class Interface > inline
    node<Interface> *
    pstade_lime_new_node(node<Interface>& parent, ustring childName)
    {
         return pstade_lime_new_node(parent, childName, overload());
    }


} // namespace new_node_detail


template< class Interface > inline
node<Interface> *
new_node(node<Interface>& parent, ustring childName)
{
    using namespace new_node_detail;

    // Trigger ADL into namespace of 'Interface',
    // but such ADL might be rejected with future C++.
    // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1893.pdf
    //
    std::auto_ptr< node<Interface> > pn(pstade_lime_new_node(parent, childName));
    if (pn.get())
        pn->detail_construct(parent, childName);

    return pn.release();
}


} } // namespace pstade::lime


#endif
