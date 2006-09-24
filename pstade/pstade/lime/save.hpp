#ifndef PSTADE_LIME_SAVE_HPP
#define PSTADE_LIME_SAVE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/equals.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/range_reference.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/ustring.hpp>
#include "./extension.hpp"
#include "./intrinsic.hpp"


namespace pstade { namespace lime {


    template< class Node, class OutIter >
    void save(Node& node, OutIter const& out);


    template< class AssocContainer, class OutIter >
    void save_attributes(AssocContainer const& attributes, OutIter const& out)
    {
        using oven::null_terminated;

        BOOST_FOREACH (
            PSTADE_UNPARENTHESIZE((std::pair<ustring, ustring>)) att,
            attributes
        )
        {
            oven::copy(" "|null_terminated, out);
            oven::copy(att.first, out);
            oven::copy("=\""|null_terminated, out);
            oven::copy(att.second, out);
            oven::copy("\""|null_terminated, out);
        }
    }


    template< class Node, class OutIter >
    void save_default(Node& node, OutIter const& out)
    {
        using oven::null_terminated;
        typedef typename oven::range_reference<Node>::type child_t;

        if (oven::equals(node.name(), i_CharData) ||
            oven::equals(node.name(), i_Reference))
        {
            oven::copy(node.attributes()[i_attName], out);
            return;
        }

        { // STag
            oven::copy("<"|null_terminated, out);
            oven::copy(node.name(), out);

            lime::save_attributes(node.attributes(), out);

            oven::copy(">"|null_terminated, out);
        }

        BOOST_FOREACH (child_t child, node) {
            lime::save(child, out);
        }

        { // ETag
            oven::copy("</"|null_terminated, out);
            oven::copy(node.name(), out);
            oven::copy(">"|null_terminated, out);
        }
    }


} } // namespace pstade::lime


// save
//

namespace pstade_lime_extension {


    // default
    template< class Node, class OutIter > inline
    void pstade_lime_(save_node, Node& node, OutIter const& out)
    {
        return pstade::lime::save_default(node, out);
    }


} // namespace pstade_lime_extension


namespace pstade { namespace lime {


    template< class Node, class OutIter > inline
    void pstade_lime_save_node(Node& node, OutIter const& out)
    {
         return pstade_lime_(pstade_lime_extension::save_node(), node, out);
    }


    template< class Node, class OutIter > inline
    void save(Node& node, OutIter const& out)
    {
        return pstade_lime_save_node(node, out); 
    }


} } // namespace pstade::lime


#endif
