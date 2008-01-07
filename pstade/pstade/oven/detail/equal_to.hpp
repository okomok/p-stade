#ifndef PSTADE_OVEN_DETAIL_EQUAL_TO_HPP
#define PSTADE_OVEN_DETAIL_EQUAL_TO_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace oven { namespace detail {


struct T_equal_to
{
    typedef bool result_type;

    template< class X, class Y >
    bool operator()(X const& x, Y const& y) const
    {
        return x == y;
    }
};

PSTADE_ADL_BARRIER(equal_to) {
    PSTADE_POD_CONSTANT((T_equal_to), equal_to) = {};
}


} } } // namespace pstade::oven::detail


#endif
