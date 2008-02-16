#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_RESULT_TYPEOF_HPP
#define PSTADE_EGG_RESULT_TYPEOF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/utility/result_of.hpp> // BOOST_RESULT_OF_NUM_ARGS
#include <pstade/in_fun_spec.hpp>

#if defined(BOOST_TYPEOF_NATIVE)
    #include <pstade/fake.hpp>
#else
    #include <pstade/result_of.hpp>
    #include <boost/type_traits/remove_reference.hpp>
#endif


namespace pstade { namespace egg {


    template<class FunCall>
    struct result_typeof;

#define PSTADE_fake(Z, N, A) fake<BOOST_PP_CAT(A, N)>()
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <pstade/egg/result_typeof.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_fake


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams PSTADE_PP_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_typeof<Fun(fparams)>
    {
#if defined(BOOST_TYPEOF_NATIVE)
        // Hmm, typeof requires type to be complete.
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL( nested, fake<Fun>()(BOOST_PP_ENUM(n, PSTADE_fake, A)) )
#else
        typedef result_of<typename boost::remove_reference<Fun>::type(fparams)> nested;
#endif
        typedef typename nested::type type;
    };


#undef  fparams

#undef  n
#endif
