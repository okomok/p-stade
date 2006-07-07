#ifndef PSTADE_OVEN_DETAIL_EQUAL_TO_HPP
#define PSTADE_OVEN_DETAIL_EQUAL_TO_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// equal_to
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


namespace pstade { namespace oven { namespace detail {


struct equal_to_fun
{
    typedef bool result_type;

    template< class X, class Y >
    bool operator()(X const& x, Y const& y) const
    {
        return x == y;
    }
};


PSTADE_INSTANCE(equal_to_fun const, equal_to, value)


} } } // namespace pstade::oven::detail


#endif
