#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_CURRY_HPP
#define PSTADE_EGG_CURRY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/bind_left1.hpp"
#include "./detail/bind_leftx.hpp"
#include "./detail/curry_result_initializers.hpp"


namespace pstade { namespace egg {


    // for curry2 implementation
    template<class Base>
    struct result_of_curry1
    {
        typedef Base type;
    };

// 2ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MAX_ARITY, <pstade/egg/curry.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()
#define n_1 BOOST_PP_DEC(n)


    // Assume fun2 is 2ary.
    // curry2(fun2)(a1)(a2)
    // => curry1(bind_left1(bind_left1, fun2))(a1)(a2)
    // => bind_left1(bind_left1, fun2)(a1)(a2)
    // => bind_left1(fun2, a1)(a2)
    // => fun2(a1, a2)

    // Assume fun4 is 4ary.
    // curry4(fun4)(a1)(a2)(a3)(a4)
    // => curry3(bind_left1(bind_left3, fun4))(a1)(a2)(a3)(a4)
    // => bind_left1(bind_left3, fun4)(a1, a2, a3)(a4)
    // => bind_left3(fun4, a1, a2, a3)(a4)
    // => fun4(a1, a2, a3, a4)

    template<class Base>
    struct BOOST_PP_CAT(result_of_curry, n) :
        BOOST_PP_CAT(result_of_curry, n_1)<
            typename detail::result_of_bind_left1<
                detail::BOOST_PP_CAT(T_bind_left, n_1), Base
            >::type
        >
    { };


    struct BOOST_PP_CAT(little_curry, n)
    {
        template<class Myself, class Base>
        struct apply :
            BOOST_PP_CAT(result_of_curry, n)<Base>
        { };

        template<class Result, class Base>
        Result call(Base base) const
        {
            Result r = BOOST_PP_CAT(PSTADE_EGG_CURRY, n)(base);
            return r;
        }
    };

    typedef function<BOOST_PP_CAT(little_curry, n), by_value> BOOST_PP_CAT(T_curry, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_curry, n)), BOOST_PP_CAT(curry, n)) = {{}};


#undef n_1
#undef  n
#endif
