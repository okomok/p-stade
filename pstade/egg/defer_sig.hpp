#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DEFER_SIG_HPP
#define PSTADE_EGG_DEFER_SIG_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a poor functor type holding 'sig'
// into the function which supports 'boost::result_of'.
//
// For "big" arity, this can't use 'function<>', hence
// can't take non-const-rvalue.
//
// As we can't detect the arity without 'lambda::bind',
// a nullary-callable function must be identified by 'defer_nullary_sig'.


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include "./detail/nonref_arg.hpp"
#include "./generator.hpp"
#include "./nullary_result_of.hpp"
#include "./use_brace_level0.hpp"
#include "./sig_template.hpp"


#if !defined(PSTADE_EGG_DEFER_SIG_MAX_ARITY)
    #define PSTADE_EGG_DEFER_SIG_MAX_ARITY 6
#endif


namespace pstade { namespace egg {


    template<class SigFun>
    struct defer_sig_error_non_nullary;


    namespace defer_sig_detail {


        template<class SigFun, class IsNullary>
        struct result_
        {
            SigFun m_base;

            typedef SigFun base_type;

            SigFun base() const
            {
                return m_base;
            }

        // 0ary
            struct result0 :
                SigFun::BOOST_NESTED_TEMPLATE sig<
                    boost::tuples::tuple<SigFun>
                >
            { };

            typedef typename
                boost::mpl::eval_if< IsNullary,
                    result0,
                    boost::mpl::identity< defer_sig_error_non_nullary<SigFun> >
                >::type
            nullary_result_type; // for that macro.

            nullary_result_type operator()() const
            {
                return m_base();
            }

        // 1ary-
            template<class FunCall>
            struct result;

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_DEFER_SIG_MAX_ARITY, <pstade/egg/defer_sig.hpp>))
            #include BOOST_PP_ITERATE()

            #include PSTADE_EGG_SIG_TEMPLATE()
        };


    } // namespace defer_sig_detail


    template<class SigFun>
    struct result_of_defer_sig
    {
        typedef
            defer_sig_detail::result_<SigFun, boost::mpl::false_>
        type;
    };

    #define PSTADE_EGG_DEFER_SIG_L {
    #define PSTADE_EGG_DEFER_SIG_R }

    typedef
        generator<
            result_of_defer_sig< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level0
        >::type
    op_defer_sig;

    PSTADE_POD_CONSTANT((op_defer_sig), defer_sig) = PSTADE_EGG_GENERATOR;


    template<class SigFun>
    struct result_of_defer_nullary_sig
    {
        typedef
            defer_sig_detail::result_<SigFun, boost::mpl::true_>
        type;
    };

    typedef
        generator<
            result_of_defer_nullary_sig< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level0
        >::type
    op_defer_nullary_sig;

    PSTADE_POD_CONSTANT((op_defer_nullary_sig), defer_nullary_sig) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::defer_sig_detail::result_, (class)(class))


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        SigFun::BOOST_NESTED_TEMPLATE sig<
            boost::tuples::tuple<
                SigFun,
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename detail::nonref_arg<A, >::type)
            >
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
