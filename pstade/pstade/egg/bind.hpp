#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BIND_HPP
#define PSTADE_EGG_BIND_HPP
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
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./apply_decl.hpp"
#include "./bind_n.hpp"
#include "./by_cref.hpp"
#include "./config.hpp"
#include "./detail/result_of_bind.hpp"


namespace pstade { namespace egg {


    namespace bind_detail {


        template<class NullaryResult>
        struct little
        {
            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

        // 1ary-
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/bind.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity
        };


    } // namespace bind_detail


    template<class NullaryResult = boost::use_default>
    struct X_bind :
        function<bind_detail::little<NullaryResult>, by_cref>
    { };

    typedef X_bind<>::function_type T_bind;
    PSTADE_POD_CONSTANT((T_bind), bind) = {{}};


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
    struct apply<Myself, Base BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)> :
        result_of<BOOST_PP_CAT(X_bind, n)<NullaryResult>(Base& BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg))>
    { };

    template<class Result, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
    Result call(Base& base BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, Arg, & arg)) const
    {
        return BOOST_PP_CAT(X_bind, n)<NullaryResult>()(base BOOST_PP_ENUM_TRAILING_PARAMS(n, arg));
    }


#undef n
#endif
