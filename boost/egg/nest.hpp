#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_NEST_HPP
#define BOOST_EGG_NEST_HPP
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
#include <boost/egg/bll/bind.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_NEST_MAX_LEVEL
#include <boost/egg/const.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/lv.hpp> // inclusion guaranteed
#include <boost/egg/lazy.hpp>
#include <boost/egg/preprocessor/cat3.hpp>


namespace boost { namespace egg {


    #define BOOST_EGG_NEST_L BOOST_EGG_LAZY_L
    #define BOOST_EGG_NEST_R BOOST_EGG_LAZY_R
    #define BOOST_EGG_NEST(F) BOOST_EGG_NEST_L F BOOST_NEST_R


    namespace nest0_detail {

        template<class Bind>
        struct nested
        {
            typedef Bind type;
        };

    }

    // 1level-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_NEST_MAX_LEVEL, <boost/egg/nest.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()
#define n_1 BOOST_PP_DEC(n)


    namespace BOOST_EGG_PP_CAT3(nest, n, _detail) {

        template<class Bind>
        struct nested :
            result_of_lazy<Bind, typename BOOST_EGG_PP_CAT3(nest, n_1, _detail)::nested<Bind>::type>
        { };

    }

    template<class Base, class Bind = use_default>
    struct BOOST_PP_CAT(result_of_nest, n) :
        result_of_lazy<
            Base,
            typename BOOST_EGG_PP_CAT3(nest, n, _detail)::nested<
                typename details::if_use_default<Bind, T_bll_bind>::type
            >::type
        >
    { };

    template<class Bind = use_default>
    struct BOOST_PP_CAT(X_nest, n) :
        X_lazy<
            typename BOOST_EGG_PP_CAT3(nest, n, _detail)::nested<
                typename details::if_use_default<Bind, T_bll_bind>::type
            >::type
        >
    { };

    typedef BOOST_PP_CAT(X_nest, n)<>::base_class BOOST_PP_CAT(T_nest, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_nest, n)), BOOST_PP_CAT(nest, n)) = BOOST_EGG_GENERATOR();


#undef  n_1
#undef  n
#endif
