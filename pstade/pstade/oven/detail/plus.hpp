#ifndef PSTADE_OVEN_DETAIL_PLUS_HPP
#define PSTADE_OVEN_DETAIL_PLUS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_const.hpp>
#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


struct baby_plus
{
    template< class Unused, class X, class Y >
    struct result :
        boost::add_const<X>
    { };

    template< class Result, class X, class Y >
    Result call(X const& x, Y const& y)
    {
        return x + y;
    }
};


PSTADE_EGG_FUNCTION(plus, baby_plus)


} } } // namespace pstade::oven::detail


#endif
