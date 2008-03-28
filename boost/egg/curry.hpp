#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_CURRY_HPP
#define BOOST_EGG_CURRY_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/detail/bind_left1.hpp>
#include <boost/egg/detail/bind_leftx.hpp>
#include <boost/egg/detail/curry_macros.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    #define BOOST_EGG_CURRY_INIT {{}}


    // for curry2 implementation
    template<class Base, class Target = use_default>
    struct result_of_curry1
    {
        typedef Base type;
    };


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, BOOST_EGG_MAX_ARITY, <boost/egg/curry.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
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


    template<class Base, class Target = Base>
    struct BOOST_PP_CAT(result_of_curry, n) :
        BOOST_PP_CAT(result_of_curry, n_1)<
            typename details::result_of_bind_left1<
                typename details::BOOST_PP_CAT(X_bind_left, n_1)<Target>::base_class,
                Base,
                Target
            >::type,
            Target
        >
    { };


    namespace BOOST_EGG_PP_CAT3(curry, n, _detail) {


        struct little
        {
            template<class Me, class Base>
            struct apply :
                BOOST_PP_CAT(result_of_curry, n)<Base>
            { };

            template<class Re, class Base>
            Re call(Base base) const
            {
                Re r = BOOST_PP_CAT(BOOST_EGG_CURRY, n)(base);
                return r;
            }
        };


    } // namespace curryN_detail


    typedef function<BOOST_EGG_PP_CAT3(curry, n, _detail)::little, by_value> BOOST_PP_CAT(T_curry, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_curry, n)), BOOST_PP_CAT(curry, n)) = BOOST_EGG_CURRY_INIT;


#undef  n_1
#undef  n
#endif
