#ifndef BOOST_EGG_FIX_HPP
#define BOOST_EGG_FIX_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.kmonos.net/wlog/52.php
// http://citeseer.ist.psu.edu/51062.html


#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include "./curry.hpp"
#include "./detail/bind_left1.hpp"
#include "./function.hpp"
#include "./make_function.hpp"


namespace pstade { namespace egg {


    namespace fix_detail {


        // fun fix base a = base (fix base) x;
        // fun uncurried_fix (base, x) = base(curry(uncurried_fix)(base))(x);

        struct little_uncurried
        {
            template<class Myself, class Base, class Arg>
            struct apply :
                result_of<
                    typename result_of<
                        Base(
                            typename result_of<
                                typename result_of<T_curry2(function<little_uncurried>)>::type(Base&)
                            >::type
                         )
                    >::type(Arg&)
                >
            { };

            template<class Result, class Base, class Arg>
            Result call(Base& base, Arg& arg) const
            {
                // Base must be curried in advance.
                return base
                    ( curry2(make_function(*this))(base) )
                    ( arg );
            }
        };


        typedef function<little_uncurried> uncurried;


    } // namespace fix_detail


    typedef result_of_curry2<fix_detail::uncurried>::type T_fix;
    PSTADE_POD_CONSTANT((T_fix), fix) = BOOST_EGG_CURRY2({{}});


    // fix(base)
    // => curry2(uncurried_fix)(base)
    // => bind_left1(bind_left1, uncurried_fix)(base)
    // => bind_left1(uncurried_fix, base)

    template<class Base>
    struct result_of_fix :
        detail::result_of_bind_left1<
            fix_detail::uncurried,
            Base
        >
    { };

    // BOOST_EGG_BIND_LEFT1_L {{}} BOOST_EGG_BIND_LEFT1_M Base BOOST_EGG_BIND_LEFT1_R
    #define BOOST_EGG_FIX_L BOOST_EGG_BIND_LEFT1_L {{}} BOOST_EGG_BIND_LEFT1_M
    #define BOOST_EGG_FIX_R BOOST_EGG_BIND_LEFT1_R
    #define BOOST_EGG_FIX(F) BOOST_EGG_FIX_L F BOOST_EGG_FIX_R


} } // namespace pstade::egg


#endif
