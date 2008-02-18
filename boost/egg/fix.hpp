#ifndef BOOST_EGG_FIX_HPP
#define BOOST_EGG_FIX_HPP
#include <boost/egg/detail/prefix.hpp>


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


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/curry.hpp> // curry2
#include <boost/egg/detail/bind_left1.hpp>
#include <boost/egg/make_function.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace fix_detail {


        // fun fix base a = base (fix base) x;
        // <=> fun uncurried_fix (base, x) = base(curry(uncurried_fix)(base))(x);

        struct little_uncurried;
        typedef function<little_uncurried, by_perfect> uncurried;

        struct little_uncurried
        {
            template<class Me, class Base, class Arg>
            struct apply :
                result_of_<
                    typename result_of_<
                        Base(
                            typename result_of_<
                                result_of_<T_curry2(uncurried &)>::type(Base &)
                            >::type
                        )
                    >::type(Arg &)
                >
            { };

            template<class Re, class Base, class Arg>
            Re call(Base &base, Arg &arg) const
            {
                // Base must be curried in advance.
                uncurried u = {*this};
                return base(curry2(u)(base))(arg);
            }
        };


    } // namespace fix_detail


    #define BOOST_EGG_FIX_INIT BOOST_EGG_CURRY2({{}})

    typedef result_of_curry2<fix_detail::uncurried>::type T_fix;
    BOOST_EGG_CONST((T_fix), fix) = BOOST_EGG_FIX_INIT;


    // fix(base)
    // => curry2(uncurried_fix)(base)
    // => bind_left1(bind_left1, uncurried_fix)(base)
    // => bind_left1(uncurried_fix, base)

    template<class Base>
    struct result_of_fix :
        details::result_of_bind_left1<
            fix_detail::uncurried,
            Base
        >
    { };

    // BOOST_EGG_BIND_LEFT1_L {{}} , Base BOOST_EGG_BIND_LEFT1_R
    #define BOOST_EGG_FIX_L BOOST_EGG_BIND_LEFT1_L {{}} ,
    #define BOOST_EGG_FIX_R BOOST_EGG_BIND_LEFT1_R
    #define BOOST_EGG_FIX(F) BOOST_EGG_FIX_L F BOOST_EGG_FIX_R


    typedef result_of_compose<T_fix, T_curry2, use_default, by_perfect>::type T_fix2;
    BOOST_EGG_CONST((T_fix2), fix2) = BOOST_EGG_COMPOSE_L BOOST_EGG_FIX_INIT, BOOST_EGG_CURRY_INIT BOOST_EGG_COMPOSE_R;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
