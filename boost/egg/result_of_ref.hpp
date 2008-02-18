#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_RESULT_OF_REF_HPP
#define BOOST_EGG_RESULT_OF_REF_HPP
#include <boost/egg/detail/prefix.hpp>


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
#include <boost/egg/detail/in_fun_spec.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    template<class FunCall>
    struct result_of_ref;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <boost/egg/result_of_ref.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams BOOST_EGG_PP_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_of_ref<Fun(fparams)> :
        result_of<
            typename remove_reference<Fun>::type(fparams)
        >
    { };


#undef  fparams

#undef  n
#endif
