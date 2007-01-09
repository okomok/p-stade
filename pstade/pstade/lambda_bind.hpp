#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_LAMBDA_BIND_HPP
#define PSTADE_LAMBDA_BIND_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // placeholders
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    struct op_lambda_bind :
        callable<op_lambda_bind>
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { };

        // 1ary-
    #define PSTADE_bind_tuple_mapper(N) \
        typename boost::lambda::detail::bind_tuple_mapper< \
            BOOST_PP_ENUM_PARAMS(N, const A) \
        >::type \
    /**/
    #define PSTADE_lambda_functor_base(N) \
        boost::lambda::lambda_functor_base< \
            boost::lambda::action<N, boost::lambda::function_action<N> >, \
            PSTADE_bind_tuple_mapper(N) \
        > \
    /**/
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/lambda_bind.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_lambda_functor_base
    #undef  PSTADE_bind_tuple_mapper

    }; // struct op_lambda_bind


    PSTADE_CONSTANT(lambda_bind, (op_lambda_bind))


    typedef boost::remove_const<boost::lambda::placeholder1_type>::type op_lambda_1;
    typedef boost::remove_const<boost::lambda::placeholder2_type>::type op_lambda_2;
    typedef boost::remove_const<boost::lambda::placeholder3_type>::type op_lambda_3;
    PSTADE_CONSTANT(lambda_1, (op_lambda_1))
    PSTADE_CONSTANT(lambda_2, (op_lambda_2))
    PSTADE_CONSTANT(lambda_3, (op_lambda_3))


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
{
    typedef
        boost::lambda::lambda_functor<
            PSTADE_lambda_functor_base(n)
        > const
    type;
};

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return PSTADE_lambda_functor_base(n)(
        PSTADE_bind_tuple_mapper(n)(
            BOOST_PP_ENUM_PARAMS(n, a)
        )
    );
}


#undef n
#endif
