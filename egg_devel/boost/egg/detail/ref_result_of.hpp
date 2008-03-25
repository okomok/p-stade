#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_REF_RESULT_OF_HPP
#define BOOST_EGG_DETAIL_REF_RESULT_OF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Boost.ResultOf doesn't support:
//     result_of<F &(int,...)>::type
// A target function sometimes may be a reference.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>


namespace boost { namespace egg { namespace details {


    template<class FunCall>
    struct ref_result_of;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <boost/egg/detail/ref_result_of.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams BOOST_EGG_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct ref_result_of<Fun(fparams)> :
        result_of_<
            typename remove_reference<Fun>::type(fparams)
        >
    { };


#undef  fparams

#undef  n
#endif
