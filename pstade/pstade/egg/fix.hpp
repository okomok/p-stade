#ifndef PSTADE_EGG_FIX_HPP
#define PSTADE_EGG_FIX_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.kmonos.net/wlog/52.php
// http://citeseer.ist.psu.edu/51062.html


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./compose.hpp"
#include "./curry.hpp" // curry2
#include "./detail/bind_left1.hpp"
#include "./make_function.hpp"


namespace pstade { namespace egg {


    namespace fix_detail {


        // fun fix base a = base (fix base) x;
        // <=> fun uncurried_fix (base, x) = base(curry(uncurried_fix)(base))(x);

        struct little_uncurried
        {
            template<class Me, class Base, class Arg>
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

            template<class Re, class Base, class Arg>
            Re call(Base& base, Arg& arg) const
            {
                // Base must be curried in advance.
                return base
                    ( curry2(make_function(*this))(base) )
                    ( arg );
            }
        };

        typedef function<little_uncurried, by_perfect> uncurried;


    } // namespace fix_detail


    #define PSTADE_EGG_FIX_INIT PSTADE_EGG_CURRY2({{}})

    typedef result_of_curry2<fix_detail::uncurried>::type T_fix;
    PSTADE_POD_CONSTANT((T_fix), fix) = PSTADE_EGG_FIX_INIT;


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

    // PSTADE_EGG_BIND_LEFT1_L {{}} , Base PSTADE_EGG_BIND_LEFT1_R
    #define PSTADE_EGG_FIX_L PSTADE_EGG_BIND_LEFT1_L {{}} ,
    #define PSTADE_EGG_FIX_R PSTADE_EGG_BIND_LEFT1_R
    #define PSTADE_EGG_FIX(F) PSTADE_EGG_FIX_L F PSTADE_EGG_FIX_R


    typedef result_of_compose<T_fix, T_curry2, boost::use_default, by_perfect>::type T_fix2;
    PSTADE_POD_CONSTANT((T_fix2), fix2) = PSTADE_EGG_COMPOSE_L PSTADE_EGG_FIX_INIT, PSTADE_EGG_CURRY_INIT PSTADE_EGG_COMPOSE_R;


} } // namespace pstade::egg


#endif
