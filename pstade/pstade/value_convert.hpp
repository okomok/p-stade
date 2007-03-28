#ifndef PSTADE_VALUE_CONVERT_HPP
#define PSTADE_VALUE_CONVERT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Same as 'boost::implicit_cast<NonReference>'.
// As the target is not reference, this can detect
// loss of range when a numeric type is converted.


#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <pstade/cast_function.hpp>


namespace pstade {


    namespace value_convert_detail {


        template<class T>
        struct is_numeric :
            boost::mpl::or_<
                boost::is_floating_point<T>,
                boost::is_integral<T>
            >
        { };


    } // namespace value_convert_detail 


    template<class To>
    struct op_value_convert
    {
        typedef To result_type;

        template<class From>
        To aux(From const& from, boost::mpl::true_) const
        {
    #if !defined(NDEBUG)
            return boost::numeric_cast<To>(from);
    #else
            return static_cast<To>(from); // suppress "loss of data" warning.
    #endif
        }

        template<class From>
        To aux(From const& from, boost::mpl::false_) const
        {
            return from;
        }

        template<class From>
        To operator()(From const& from) const
        {
            BOOST_MPL_ASSERT_NOT((boost::is_reference<To>));

            typedef typename boost::mpl::and_<
                value_convert_detail::is_numeric<To>,
                value_convert_detail::is_numeric<From>
            >::type is_numeric_castable;
            return aux(from, is_numeric_castable());
        }
    };


    PSTADE_CAST_FUNCTION1(value_convert, op_value_convert, 1)


} // namespace pstade


#endif
