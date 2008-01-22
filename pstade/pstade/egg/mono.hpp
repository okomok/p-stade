#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_MONO_HPP
#define PSTADE_EGG_MONO_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/implicit_cast.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/plain.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    namespace mono_detail {


        template<class Base, class Signature>
        struct result_;

        // 0ary-
    #define PSTADE_forward(Z, N, _) boost::implicit_cast<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/mono.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_forward


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
    #define PSTADE_EGG_MONO(F) PSTADE_EGG_MONO_L F PSTADE_EGG_MONO_R


    namespace mono_detail {


        template<class Signature>
        struct little
        {
            template<class Myself, class Base>
            struct apply :
                result_of_mono<Base, Signature>
            { };

            template<class Result, class Base>
            Result call(Base base) const
            {
                Result r = PSTADE_EGG_MONO(base);
                return r;
            }
        };


    } // namespace mono_detail


    template<class Signature>
    struct X_mono :
        function<mono_detail::little<Signature>, by_value>
    { };

    template<class Signature, class Base> inline
    typename result_of<X_mono<Signature>(Base&)>::type mono(Base base)
    {
        return X_mono<Signature>()(base);
    }


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class ResultType BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_<Base, ResultType(BOOST_PP_ENUM_PARAMS(n, A))>
    {
        typedef Base base_type;

#if n == 1
        typedef typename plain<A0>::type argument_type;
#elif n == 2
        typedef typename plain<A0>::type first_argument_type;
        typedef typename plain<A1>::type second_argument_type;
#endif

        typedef typename
            eval_if_use_default<ResultType,
                result_of<Base const(BOOST_PP_ENUM_PARAMS(n, A))>
            >::type
        result_type;

        Base m_base;

        Base const& base() const
        {
            return m_base;
        }

        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
        {
            return m_base(BOOST_PP_ENUM(n, PSTADE_forward, ~));
        }
    };


#undef n
#endif
