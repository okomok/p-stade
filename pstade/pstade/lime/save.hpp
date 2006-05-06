#ifndef PSTADE_LIME_SAVE_HPP
#define PSTADE_LIME_SAVE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/ustring.hpp>
#include "./intrinsic.hpp"
#include "./node.hpp"


namespace pstade { namespace lime {


namespace save_detail {


    template< class Interface, class OutIter >
    void aux(node<Interface>& parent, OutIter out)
    {
        using oven::null_terminated;

        if (oven::equals(parent.name(), i_CharData) ||
            oven::equals(parent.name(), i_Reference))
        {
            oven::copy(parent.att(i_attName), out);
            return;
        }

        { // STag
            oven::copy("<"|null_terminated, out);
            oven::copy(parent.name(), out);

            BOOST_FOREACH (
                comma_protect<void(std::pair<ustring, ustring>)>::type att,
                parent.attributes()
            ) {
                oven::copy(" "|null_terminated, out);
                oven::copy(att.first, out);
                oven::copy("=\""|null_terminated, out);
                oven::copy(att.second, out);
                oven::copy("\""|null_terminated, out);
            }

            oven::copy(">"|null_terminated, out);
        }

        BOOST_FOREACH (node<Interface>& child, parent) {
            save_detail::aux(child, out);
        }

        { // ETag
            oven::copy("</"|null_terminated, out);
            oven::copy(parent.name(), out);
            oven::copy(">"|null_terminated, out);
        }
    }


} // namespace save_detail


template< class Interface, class OutIter >
void save(node<Interface>& root, OutIter out)
{
    BOOST_FOREACH (node<Interface>& child, root) {
        save_detail::aux(child, out);
    }
}


} } // namespace pstade::lime


#endif
