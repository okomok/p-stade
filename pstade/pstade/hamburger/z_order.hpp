#ifndef PSTADE_HAMBURGER_Z_ORDER_HPP
#define PSTADE_HAMBURGER_Z_ORDER_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/if_debug.hpp>
#include <pstade/instance.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>
#include "./log.hpp"


namespace pstade { namespace hamburger {


struct z_order_function
{
    typedef bool result_type;

    template< class Node >
    bool operator()(Node& node1, Node& node2) const
    {
        try {
            int zIndex1 = pstade::lexical(node1%Name_zIndex);
            int zIndex2 = pstade::lexical(node2%Name_zIndex);
            return zIndex1 < zIndex2;
        }
        catch (boost::bad_lexical_cast& PSTADE_IF_DEBUG(err)) {
            PSTADE_IF_DEBUG (
                log << err.what();
            )
            return false;
        }
    }
};


PSTADE_INSTANCE(const z_order_function, z_order, value);


} } // namespace pstade::hamburger


#endif
