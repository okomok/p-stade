#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    template< class To, class From > inline
    To integral_cast(From from)
    {
        BOOST_MPL_ASSERT((boost::is_integral<To>));
        BOOST_MPL_ASSERT((boost::is_integral<From>));

        return boost::numeric_cast<To>(from);
    }


    struct integral_cast_fun
    {
        // In fact, 'PSTADE_PIPABLE' doesn't pose 'result_of' support.
        template< class Signature >
        struct result;

        template< class Self, class From, class TypeTo >
        struct result<Self(From, TypeTo)> :
            to_type<TypeTo>
        { };

        template< class From, class TypeTo >
        typename to_type<TypeTo>::type operator()(From from, TypeTo) const
        {
            return pstade::integral_cast<typename to_type<TypeTo>::type>(from);
        }
    };

    PSTADE_AUTO_CASTABLE(integral, integral_cast_fun)
    PSTADE_PIPABLE(to_integer, integral_fun)


} // namespace pstade


#endif
