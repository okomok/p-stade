#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_RANGE_BASED_HPP
#define PSTADE_OVEN_RANGE_BASED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // lambda_functor
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp> 
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/as.hpp>
#include <pstade/callable.hpp>
#include <pstade/lambda_result_of.hpp> // inclusion guaranteed
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace range_based_detail {


    template< class IterBased >
    struct op_result :
        callable< op_result<IterBased> >
    {
        template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
        struct apply
        { }; // complete for SFINAE.

        // 1ary
        template< class Myself, class A0 >
        struct apply<Myself, A0> :
            boost::result_of<
                IterBased(
                    typename range_iterator<A0>::type,
                    typename range_iterator<A0>::type
                )
            >
        { };

        template< class Result, class A0 >
        Result call(A0& a0) const
        {
            return m_fun(
                boost::begin(a0),
                boost::end(a0)
            );
        }

        // 2ary-
    #define PSTADE_ref(Z, N, A) BOOST_PP_CAT(A, N) &
    #define PSTADE_as_ref(Z, N, A) as_ref(BOOST_PP_CAT(A, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/range_based.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_as_ref
    #undef  PSTADE_ref

        explicit op_result()
        { }

        explicit op_result(IterBased const& fun) :
            m_fun(fun)
        { }

        typedef IterBased base_type;

        IterBased const& base() const
        {
            return m_fun;
        }

    private:
        IterBased m_fun;
    };


} // namespace range_based_detail


// PSTADE_OBJECT_GENERATOR(range_based, (range_based_detail::op_result< deduce<_1, to_value> >))


template< class SigFun >
range_based_detail::op_result<
    typename boost::lambda::as_lambda_functor<SigFun>::type
>
range_based()
{
    return
        range_based_detail::op_result<
            typename boost::lambda::as_lambda_functor<SigFun>::type
        >( boost::lambda::to_lambda_functor(SigFun()) );
}


template< class Function >
range_based_detail::op_result<Function>
range_based(Function fun)
{
    return range_based_detail::op_result<Function>(fun);
}


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<
        IterBased(
            typename range_iterator<A0>::type,
            typename range_iterator<A0>::type,
            BOOST_PP_ENUM_SHIFTED(n, PSTADE_ref, A)
        )
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(
        as_ref(boost::begin(a0)),
        as_ref(boost::end(a0)),
        BOOST_PP_ENUM_SHIFTED(n, PSTADE_as_ref, a)
    );
}


#undef n
#endif
