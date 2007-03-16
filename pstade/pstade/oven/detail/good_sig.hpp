#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_GOOD_SIG_HPP
#define PSTADE_OVEN_DETAIL_GOOD_SIG_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a poor functor type holding 'sig'
// into the function which supports 'boost::result_of'.
//
// For "big" arity, this can't use 'callable' hence
// can't take non-const-rvalue. But this is always
// called from 'range_basedN' with 'as_cref'.


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/callable.hpp> // callable_argument
#include <pstade/lambda_sig.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>


#if !defined(PSTADE_OVEN_DETAIL_GOOD_SIG_MAX_ARITY)
    #define PSTADE_OVEN_DETAIL_GOOD_SIG_MAX_ARITY 6
#endif


namespace pstade { namespace oven { namespace detail {


template< class SigFun >
struct good_sig_return_op :
    lambda_sig
{
    template< class FunCall >
    struct result
    { }; // complete for SFINAE.

    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_DETAIL_GOOD_SIG_MAX_ARITY, <pstade/oven/detail/good_sig.hpp>))
    #include BOOST_PP_ITERATE()

    explicit good_sig_return_op()
    { }

    explicit good_sig_return_op(SigFun const& fun) :
        m_fun(fun)
    { }

    typedef SigFun base_type;

    SigFun const& base() const
    {
        return m_fun;
    }

private:
    SigFun m_fun;
};


PSTADE_OBJECT_GENERATOR(good_sig, (good_sig_return_op< deduce<_1, to_value> >))


} } } // namespace pstade::oven::detail


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n) :
        SigFun::BOOST_NESTED_TEMPLATE sig<
            boost::tuples::tuple<
                SigFun,
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename callable_argument<A, >::type)
            >
        >
    { };

public:
    template< class Fun, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_fun(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
