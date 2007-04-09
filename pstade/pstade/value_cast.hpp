#ifndef PSTADE_VALUE_CAST_HPP
#define PSTADE_VALUE_CAST_HPP


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


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <pstade/specified.hpp>


#define PSTADE_VALUE_CONVERT(From, To)

namespace pstade {


    namespace value_cast_detail {


        template<class T>
        struct is_numeric :
            boost::mpl::or_<
                boost::is_floating_point<T>,
                boost::is_integral<T>
            >
        { };


    } // namespace value_cast_detail 


    template<class To>
    struct op_value_cast
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
                value_cast_detail::is_numeric<To>,
                value_cast_detail::is_numeric<From>
            >::type is_numeric_castable;
            return aux(from, is_numeric_castable());
        }

#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        // For some reason, msvc-7.1 linker is confused by this non-template.
        // (Anyway he works thanks to 'numeric_cast' without this.)
        // Note that 'enable_if' with template also can work around this bug.
        To operator()(To const& from) const
        {
            return from;
        }
#endif
    };


    PSTADE_SPECIFIED1(value_cast, op_value_cast, 1)


} // namespace pstade


#endif
