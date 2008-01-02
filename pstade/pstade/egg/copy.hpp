#ifndef PSTADE_EGG_COPY_HPP
#define PSTADE_EGG_COPY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
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
#include <pstade/adl_barrier.hpp>
#include "./by_cref.hpp"
#include "./specified.hpp"


namespace pstade { namespace egg {


    namespace copy_detail {


        template<class T>
        struct is_numeric :
            boost::mpl::or_<
                boost::is_floating_point<T>,
                boost::is_integral<T>
            >
        { };


        template<class To>
        struct little
        {
            template<class Myself, class From>
            struct apply
            {
                typedef To type;
            };

            template<class Result, class From>
            To call(From& from) const
            {
                BOOST_MPL_ASSERT_NOT((boost::is_reference<To>));
                return aux(from, boost::mpl::and_< is_numeric<To>, is_numeric<From> >());
            }

            template<class From>
            To aux(From& from, boost::mpl::true_) const
            {
#if !defined(NDEBUG)
                return boost::numeric_cast<To>(from);
#else
                return static_cast<To>(from); // suppress "loss of data" warning.
#endif
            }

            template<class From>
            To aux(From& from, boost::mpl::false_) const
            {
                return from;
            }
        };


    } // namespace copy_detail


    template<class To>
    struct X_copy :
        function<copy_detail::little<To>, by_cref>
    { };


    PSTADE_ADL_BARRIER(copy) { // for 'std'
    #define  PSTADE_EGG_SPECIFIED_PARAMS (copy, X_copy, (class), (1))
    #include PSTADE_EGG_SPECIFIED()
    }


} } // namespace pstade::egg


#endif
