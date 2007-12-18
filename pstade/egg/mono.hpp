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


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/add_reference.hpp>
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


        template<class Base, class Signature>
        struct result_;


        // 0ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/mono.hpp>))
        #include BOOST_PP_ITERATE()


    } // namespace mono_detail


    template<class Base, class Signature>
    struct result_of_mono
    {
        typedef
            mono_detail::result_<Base, Signature>
        type;
    };


    #define PSTADE_EGG_MONO_L {
    #define PSTADE_EGG_MONO_R }


    namespace mono_detail {


        template<class Signature>
        struct baby
        {
            template<class Myself, class Base>
            struct apply :
                result_of_mono<Base, Signature>
            { };

            template<class Result, class Base>
            Result call(Base base) const
            {
                Result r = PSTADE_EGG_MONO_L base PSTADE_EGG_MONO_R;
                return r;
            }
        };


    } // namespace mono_detail


    template<class Signature>
    struct X_mono :
        function<mono_detail::baby<Signature>, by_value>
    { };


    PSTADE_EGG_SPECIFIED1(mono, X_mono, (class))


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class ResultType BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_<Base, ResultType(BOOST_PP_ENUM_PARAMS(n, A))>
    {
        Base m_base;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

#if n == 1
        typedef typename argument_type<A0>::type argument_type;
#elif n == 2
        typedef typename argument_type<A0>::type first_argument_type;
        typedef typename argument_type<A1>::type second_argument_type;
#endif

        typedef typename
            eval_if_use_default<ResultType,
                result_of<Base const(PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::add_reference<A, >::type))>
            >::type
        result_type;

        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
        {
            return m_base(BOOST_PP_ENUM_PARAMS(n, a));
        }
    };


#undef n
#endif
