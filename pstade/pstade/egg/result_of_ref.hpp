#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_RESULT_OF_REF_HPP
#define PSTADE_EGG_RESULT_OF_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Boost.ResultOf doesn't support:
//     result_of<F&(int,...)>::type
// A target function sometimes may be a reference.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/in_fun_spec.hpp>
#include <pstade/result_of.hpp>


namespace pstade { namespace egg {


    template<class FunCall>
    struct result_of_ref;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <pstade/egg/result_of_ref.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams PSTADE_PP_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_of_ref<Fun(fparams)> :
        result_of<
            typename boost::remove_reference<Fun>::type(fparams)
        >
    { };


#undef  fparams

#undef  n
#endif
