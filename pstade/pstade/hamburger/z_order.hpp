#ifndef PSTADE_HAMBURGER_Z_ORDER_HPP
#define PSTADE_HAMBURGER_Z_ORDER_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/if_debug.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/singleton.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>
#include "./log.hpp"


namespace pstade { namespace hamburger {


    struct op_z_order
    {
        typedef bool result_type;

        template< class Node >
        bool operator()(Node& node1, Node& node2) const
        {
            try {
                int zIndex1 = node1%Name_zIndex|lexicalized;
                int zIndex2 = node2%Name_zIndex|lexicalized;
                return zIndex1 < zIndex2;
            }
            catch (boost::bad_lexical_cast const& PSTADE_IF_DEBUG(err)) {
                PSTADE_IF_DEBUG (
                    log << err.what();
                )
                return false;
            }
        }
    };

    PSTADE_SINGLETON_CONST(z_order, op_z_order)


    struct op_z_order_sort
    {
        typedef void result_type;

        template< class Node >
        void operator()(Node& node) const
        {
            node.sort(z_order);
        }
    };

    PSTADE_SINGLETON_CONST(z_order_sort, op_z_order_sort)


} } // namespace pstade::hamburger


#endif
