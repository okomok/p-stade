#ifndef PSTADE_OVEN_DETAIL_LESS_THAN_HPP
#define PSTADE_OVEN_DETAIL_LESS_THAN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


namespace pstade { namespace oven { namespace detail {


struct less_than_fun
{
    typedef bool result_type;

    template< class X, class Y >
    bool operator()(X const& x, Y const& y) const
    {
        return x < y;
    }
};


PSTADE_INSTANCE(less_than_fun const, less_than, value)


} } } // namespace pstade::oven::detail


#endif
