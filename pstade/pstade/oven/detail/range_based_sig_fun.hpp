#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED_SIG_FUN_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED_SIG_FUN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>
#include "../range_based1.hpp"
#include "../range_based2.hpp"


namespace pstade { namespace oven { namespace detail {


template< class SigFun >
struct sig_forward_result :
    callable< sig_forward_result<SigFun> >
{
    template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
    struct apply
    { }; // complete for SFINAE.

    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/detail/range_based_sig_fun.hpp>))
    #include BOOST_PP_ITERATE()

    explicit sig_forward_result()
    { }

    explicit sig_forward_result(SigFun const& fun) :
        m_fun(fun)
    { }

private:
    SigFun m_fun;
};


// This converts a poor functor type holding 'sig'
// into the function which supports 'boost::result_of'.
PSTADE_OBJECT_GENERATOR(sig_forward, (sig_forward_result< deduce<_1, to_value> >))


template< class SigFun >
struct range_based1_sig_fun :
    boost::result_of<
        op_range_based1(
            typename boost::result_of<op_sig_forward(SigFun)>::type
        )
    >
{ };

#define PSTADE_OVEN_DETAIL_RANGE_BASED1_SIG_FUN(R, _, Name) \
    PSTADE_CONSTANT(Name, (::pstade::oven::detail::range_based1_sig_fun< ::boost::lambda::ll::Name >::type)) \
/**/


template< class SigFun >
struct range_based2_sig_fun :
    boost::result_of<
        op_range_based2(
            typename boost::result_of<op_sig_forward(SigFun)>::type
        )
    >
{ };

#define PSTADE_OVEN_DETAIL_RANGE_BASED2_SIG_FUN(R, _, Name) \
    PSTADE_CONSTANT(Name, (::pstade::oven::detail::range_based2_sig_fun< ::boost::lambda::ll::Name >::type)) \
/**/


} } } // namespace pstade::oven::detail


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    SigFun::BOOST_NESTED_TEMPLATE sig<
        boost::tuples::tuple<
            SigFun,
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
