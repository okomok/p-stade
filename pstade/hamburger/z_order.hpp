#ifndef PSTADE_HAMBURGER_Z_ORDER_HPP
#define PSTADE_HAMBURGER_Z_ORDER_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lexicalize.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unused.hpp>
#include "./log.hpp"


namespace pstade { namespace hamburger {


    struct T_z_order
    {
        typedef bool result_type;

        template< class Node >
        bool operator()(Node& node1, Node& node2) const
        {
            try {
                int zIndex1 = node1%Name_zIndex|egg::lexicalize();
                int zIndex2 = node2%Name_zIndex|egg::lexicalize();
                return zIndex1 < zIndex2;
            }
            catch (boost::bad_lexical_cast const& err) {
#if !defined(NDEBUG)
                log << err.what();
#else
                unused(err);    
#endif
                return false;
            }
        }
    };

    PSTADE_POD_CONSTANT((T_z_order), z_order) = {};


    struct T_z_order_sort
    {
        typedef void result_type;

        template< class Node >
        void operator()(Node& node) const
        {
            node.sort(z_order);
        }
    };

    PSTADE_POD_CONSTANT((T_z_order_sort), z_order_sort) = {};


} } // namespace pstade::hamburger


#endif
