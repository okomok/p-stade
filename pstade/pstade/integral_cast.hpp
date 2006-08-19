#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


template< class To, class From > inline
To integral_cast(From from)
{
    BOOST_MPL_ASSERT((boost::is_integral<To>));
    BOOST_MPL_ASSERT((boost::is_integral<From>));

    return boost::numeric_cast<To>(from);
}


struct integral_cast_class
{
    template< class To, class From >
    static To call(From from)
    {
        return pstade::integral_cast<To>(from);
    }
};


PSTADE_EGG_FUNCTION(integral, egg::baby_auto<integral_cast_class>)
PSTADE_EGG_PIPABLE(to_integer, egg::baby_auto<integral_cast_class>)


} // namespace pstade


#endif
