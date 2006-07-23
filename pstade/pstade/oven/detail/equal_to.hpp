#ifndef PSTADE_OVEN_DETAIL_EQUAL_TO_HPP
#define PSTADE_OVEN_DETAIL_EQUAL_TO_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'equal_to' at Boost.StringAlgorithm
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


struct baby_equal_to
{
    template< class Unused, class X, class Y >
    struct result
    {
        typedef bool type;
    };

    template< class Result, class X, class Y >
    Result call(X const& x, Y const& y)
    {
        return x == y;
    }
};


PSTADE_EGG_FUNCTION(equal_to, baby_equal_to)


} } } // namespace pstade::oven::detail


#endif
