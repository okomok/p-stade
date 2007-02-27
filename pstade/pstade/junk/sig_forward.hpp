#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_SIG_FORWARD_HPP
#define PSTADE_OVEN_DETAIL_SIG_FORWARD_HPP


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


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/callable.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven { namespace detail {


template< class SigFun >
struct sig_forward_result :
    callable< sig_forward_result<SigFun> >
{
    template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
    struct apply
    { }; // complete for SFINAE.

    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/detail/sig_forward.hpp>))
    #include BOOST_PP_ITERATE()

    explicit sig_forward_result()
    { }

    explicit sig_forward_result(SigFun const& fun) :
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


PSTADE_OBJECT_GENERATOR(sig_forward, (sig_forward_result< deduce<_1, to_value> >))


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
