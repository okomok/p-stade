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


namespace pstade { namespace oven { namespace detail {


struct equal_to
{
    template< class X, class Y >
    bool operator()(const X& x, const Y& y) const
    {
        return x == y;
    }
};


} } } // namespace pstade::oven::detail


#endif
