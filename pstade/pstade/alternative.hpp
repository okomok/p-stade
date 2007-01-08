#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_ALTERNATIVE_HPP
#define PSTADE_ALTERNATIVE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/template_arity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>


#if !defined (PSTADE_ALTERNATIVE_MAX_ARITY)
    #define PSTADE_ALTERNATIVE_MAX_ARITY 5 // for MPL PlaceholderExpression
#endif


namespace pstade {


    namespace alternative_detail {


        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_ALTERNATIVE_MAX_ARITY, class T, void)>
        struct vector
        {
    #define PSTADE_typedef_argument(z, N, _) typedef BOOST_PP_CAT(T, N) BOOST_PP_CAT(argument, N);

            typedef vector type;
            BOOST_PP_REPEAT(PSTADE_ALTERNATIVE_MAX_ARITY, PSTADE_typedef_argument, ~)

    #undef  PSTADE_typedef_argument
        };


    } // namespace alternative_detail


    // GCC needs arity for specialization.
#define PSTADE_with_arity() \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM( \
        class Arity = ::boost::mpl::int_< ::boost::mpl::aux::template_arity<X>::value > \
    ) \
/**/
#define PSTADE_arity(N) \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(::boost::mpl::int_<N>) \
/**/


    template<
        class X
        PSTADE_with_arity()
    >
    struct alternative;


    template<
        class Vector,
        class X
        PSTADE_with_arity()
    >
    struct alternative_affect;


    // 1ary

    template<
        template<class _0> class X,
        class T0
    >
    struct alternative<X<T0> PSTADE_arity(1)>
    {
        typedef alternative_detail::vector<T0> type;
    };

    template<
        class Vector,
        template<class _0> class X,
        class T0
    >
    struct alternative_affect<Vector, X<T0> PSTADE_arity(1)>
    {
        typedef X<typename Vector::argument0> type;
    };


    // 2ary-

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_ALTERNATIVE_MAX_ARITY, <pstade/alternative.hpp>))
    #include BOOST_PP_ITERATE()


#undef PSTADE_arity
#undef PSTADE_with_arity


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<
    template<BOOST_PP_ENUM_PARAMS(n, class _)> class X,
    BOOST_PP_ENUM_PARAMS(n, class T)
>
struct alternative<X<BOOST_PP_ENUM_PARAMS(n, T)> PSTADE_arity(n)>
{
    typedef alternative_detail::vector<BOOST_PP_ENUM_PARAMS(n, T)> type;
};

template<
    class Vector,
    template<BOOST_PP_ENUM_PARAMS(n, class _)> class X,
    BOOST_PP_ENUM_PARAMS(n, class T)
>
struct alternative_affect<Vector, X<BOOST_PP_ENUM_PARAMS(n, T)> PSTADE_arity(n)>
{
    typedef X<BOOST_PP_ENUM_PARAMS(n, typename Vector::argument)> type;
};


#undef n
#endif
