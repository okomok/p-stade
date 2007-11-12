#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_MONO_HPP
#define PSTADE_EGG_MONO_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./specified.hpp"


namespace pstade { namespace egg {


    namespace mono_detail {


        // This should be cv-qualifier sensitive?
        template<class A>
        struct argument_type :
            remove_cvr<A>
        { };


        template<class Base, class Sequence, class ResultType, int Arity = boost::mpl::size<Sequence>::value>
        struct result_;


        // 0ary-
    #define PSTADE_param(Z, N, _) PSTADE_PP_CAT3(parameter, N, _type)
    #define PSTADE_typedef_param(Z, N, _) typedef typename boost::mpl::at_c<Sequence, N>::type PSTADE_param(Z, N, _);
    #define PSTADE_meta_arg(Z, N, _) typename boost::add_reference<PSTADE_param(Z, N, _)>::type
    #define PSTADE_param_arg(Z, N, _) PSTADE_param(Z, N, _) BOOST_PP_CAT(a, N)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/mono.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_param_arg
    #undef  PSTADE_meta_arg
    #undef  PSTADE_typedef_param
    #undef  PSTADE_param


    } // namespace mono_detail


    template<class Base, class Sequence, class ResultType = boost::use_default>
    struct result_of_mono
    {
        typedef
            mono_detail::result_<Base, Sequence, ResultType>
        type;
    };


    #define PSTADE_EGG_MONO_L {
    #define PSTADE_EGG_MONO_R }


    namespace mono_detail {


        template<class Sequence, class ResultType>
        struct baby
        {
            template<class Myself, class Base>
            struct apply :
                result_of_mono<Base, Sequence, ResultType>
            { };

            template<class Result, class Base>
            Result call(Base base) const
            {
                Result r = PSTADE_EGG_MONO_L base PSTADE_EGG_MONO_R;
                return r;
            }
        };


        // 'generator' with 'result_' didn't work under gcc3.4/4.1 after all.
        template<class Sequence, class ResultType>
        struct pod_
        {
            typedef function<baby<Sequence, ResultType>, by_value> type;
        };


    } // namespace mono_detail


    template<class Sequence, class ResultType = boost::use_default>
    struct X_mono :
        mono_detail::pod_<Sequence, ResultType>::type
    {
        typedef typename mono_detail::pod_<Sequence, ResultType>::type pod_type;
    };


    PSTADE_EGG_SPECIFIED1(mono, X_mono, (class))


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class Sequence, class ResultType>
    struct result_<Base, Sequence, ResultType, n>
    {
        Base m_base;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

        BOOST_PP_REPEAT(n, PSTADE_typedef_param, ~)

#if n == 1
        typedef typename argument_type<parameter0_type>::type argument_type;
#elif n == 2
        typedef typename argument_type<parameter0_type>::type first_argument_type;
        typedef typename argument_type<parameter1_type>::type second_argument_type;
#endif

        typedef typename
            eval_if_use_default<ResultType,
                result_of<Base const(BOOST_PP_ENUM(n, PSTADE_meta_arg, ~))>
            >::type
        result_type;

        result_type operator()(BOOST_PP_ENUM(n, PSTADE_param_arg, ~)) const
        {
            return m_base(BOOST_PP_ENUM_PARAMS(n, a));
        }
    };


#undef n
#endif
