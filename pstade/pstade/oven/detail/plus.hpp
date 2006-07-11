#ifndef PSTADE_OVEN_DETAIL_PLUS_HPP
#define PSTADE_OVEN_DETAIL_PLUS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


struct baby_plus
{
    template< class Unused, class X, class X_ >
    struct result
    {
        typedef X type;
    };

    template< class Result, class X >
    Result call(X const& x1, X const& x2)
    {
        return x1 + x2;
    }
};


PSTADE_EGG_FUNCTION(plus, baby_plus)


} } } // namespace pstade::oven::detail


#endif
