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
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    template< class To, class From > inline
    To integral_cast(From from)
    {
        BOOST_MPL_ASSERT((boost::is_integral<To>));
        BOOST_MPL_ASSERT((boost::is_integral<From>));

        return boost::numeric_cast<To>(from);
    }


    struct integral_cast_fun :
        to_type_cast_result
    {
        template< class From, class Type_To >
        typename to_type<Type_To>::type operator()(From const& from, Type_To) const
        {
            return pstade::integral_cast<typename to_type<Type_To>::type>(from);
        }
    };

    PSTADE_SINGLETON_CONST(integral_cast_fun, integral_cast_)
    PSTADE_PIPABLE(to_integer, boost::result_of<auto_castable_fun(integral_cast_fun)>::type)


} // namespace pstade


#endif
