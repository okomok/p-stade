#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_RESULT_OF_BIND_HPP
#define BOOST_EGG_DETAIL_RESULT_OF_BIND_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/bind_n.hpp>
#include <boost/egg/config.hpp>
#include <boost/egg/detail/pp_enum_params_with.hpp>


namespace boost { namespace egg {


    template<class Base, class NullaryResult, BOOST_EGG_PP_ENUM_PARAMS_WITH(BOOST_EGG_MAX_LINEAR_ARITY, class Arg, = void)>
    struct result_of_bind;

#define BOOST_EGG_max_arity BOOST_PP_DEC(BOOST_EGG_MAX_LINEAR_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_max_arity, <boost/egg/detail/result_of_bind.hpp>))
    #include BOOST_PP_ITERATE()
#undef  BOOST_EGG_max_arity


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
    struct result_of_bind<Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)> :
        BOOST_PP_CAT(result_of_bind, n)<Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)>
    { };


#undef  n
#endif
