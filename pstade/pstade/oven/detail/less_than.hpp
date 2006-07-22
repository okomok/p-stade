#ifndef PSTADE_OVEN_DETAIL_LESS_THAN_HPP
#define PSTADE_OVEN_DETAIL_LESS_THAN_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


struct baby_less_than
{
    template< class Unused, class X, class Y >
    struct result
    {
        typedef bool type;
    };

    template< class Result, class X, class Y >
    Result call(X const& x, Y const& y)
    {
        return x < y;
    }
};


PSTADE_EGG_FUNCTION(less_than, baby_less_than)


} } } // namespace pstade::oven::detail


#endif
