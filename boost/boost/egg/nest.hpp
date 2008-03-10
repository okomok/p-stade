#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_NEST_HPP
#define BOOST_EGG_NEST_HPP


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
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_NEST_LEVEL
#include <boost/egg/const.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/nest_placeholder.hpp> // inclusion guaranteed
#include <boost/egg/identity.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/preprocessor/cat3.hpp>


namespace boost { namespace egg {


// level0
    template<class Bind = use_default>
    struct X_nest0 :
        X_identity<by_value>
    { };

    typedef X_nest0<>::base_class T_nest0;
    BOOST_EGG_CONST((T_nest0), nest0) = {{}};


// level1-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_NEST_LEVEL, <boost/egg/nest.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    namespace BOOST_EGG_PP_CAT3(nest, n, _detail) {
#if n == 1
        template<class Bind>
        struct with
        {
            typedef Bind type;
        };
#else
        template<class Bind>
        struct with :
            result_of_lazy<
                Bind,
                typename BOOST_EGG_PP_CAT3(nest, BOOST_PP_DEC(n), _detail)::with<Bind>::type
            >
        { };
#endif
    }

    template<class Bind = use_default>
    struct BOOST_PP_CAT(X_nest, n) :
        X_lazy<
            typename BOOST_EGG_PP_CAT3(nest, n, _detail)::with<
                typename details::if_use_default<Bind, T_bll_bind>::type
            >::type
        >
    { };

    typedef BOOST_PP_CAT(X_nest, n)<>::base_class BOOST_PP_CAT(T_nest, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_nest, n)), BOOST_PP_CAT(nest, n)) = {{}};


#undef  n
#endif
