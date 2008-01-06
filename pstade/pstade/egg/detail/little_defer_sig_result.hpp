#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_DEFER_SIG_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_DEFER_SIG_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include "../apply_decl.hpp"
#include "../bll/config.hpp"
#include "../by_ref.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class SigFun>
    struct defer_sig_error_non_nullary;


    template<class SigFun, class IsNullary>
    struct little_defer_sig_result
    {
        SigFun m_base;

        typedef SigFun base_type;

        SigFun base() const
        {
            return m_base;
        }

    // 0ary
        struct result0 :
            SigFun::template sig<
                boost::tuples::tuple<SigFun>
            >
        { };

        typedef typename
            boost::mpl::eval_if< IsNullary,
                result0,
                boost::mpl::identity< defer_sig_error_non_nullary<SigFun> >
            >::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return m_base();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, <pstade/egg/detail/little_defer_sig_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        SigFun::template sig<
            boost::tuples::tuple<
                SigFun,
                BOOST_PP_ENUM_PARAMS(n, A)
            >
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
