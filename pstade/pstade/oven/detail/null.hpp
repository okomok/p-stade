#ifndef PSTADE_OVEN_DETAIL_NULL_HPP
#define PSTADE_OVEN_DETAIL_NULL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven { namespace detail {


struct baby_null
{
    template< class Unused, class X >
    struct result
    {
        typedef void type;
    };

    template< class Result, class X >
    Result call(X const& x)
    {
        pstade::unused(x);
    }
};


PSTADE_EGG_FUNCTION_(null_, baby_null)


} } } // namespace pstade::oven::detail


#endif
