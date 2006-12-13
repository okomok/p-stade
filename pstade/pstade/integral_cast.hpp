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
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    template< class To, class From > inline
    To integral_cast(From const& from)
    {
        BOOST_MPL_ASSERT((boost::is_integral<To>));
        BOOST_MPL_ASSERT((boost::is_integral<From>));

        return boost::numeric_cast<To>(from);
    }


    struct op_integral_cast :
        to_type_cast_result
    {
        template< class From, class Type_To >
        typename to_type<Type_To>::type operator()(From const& from, Type_To) const
        {
            return pstade::integral_cast<typename to_type<Type_To>::type>(from);
        }
    };

    PSTADE_CONSTANT(integral_cast_, (op_integral_cast))
    PSTADE_PIPABLE(to_integer, (boost::result_of<op_auto_castable(op_integral_cast)>::type))


} // namespace pstade


#endif
