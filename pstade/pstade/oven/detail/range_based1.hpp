#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED1_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED1_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Yet another implementation using 'fuse/unfuse' and
// Boost.Fusion will be interesting.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/to_ref.hpp>
#include "../range_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IterBased >
struct range_based1_return_op :
    callable< range_based1_return_op<IterBased> >
{
    template< class Myself, class Range0, PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_CALLABLE_MAX_ARITY, class A, = void) >
    struct apply
    { }; // complete for SFINAE.

    // rng0 + 0ary
    template< class Myself, class Range0 >
    struct apply<Myself, Range0> :
        result_of<
            IterBased const(
                typename range_iterator<Range0>::type const&,
                typename range_iterator<Range0>::type const&
            )
        >
    { };

    template< class Result, class Range0 >
    Result call(Range0& rng0) const
    {
        return m_fun(
            to_cref(boost::begin(rng0)),
            to_cref(boost::end(rng0))
        );
    }

    // rng0 + 1ary-
#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/oven/detail/range_based1.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity

    explicit range_based1_return_op()
    { }

    explicit range_based1_return_op(IterBased fun) :
        m_fun(fun)
    { }

    typedef IterBased base_type;

    IterBased base() const
    {
        return m_fun;
    }

private:
    IterBased m_fun;
};


PSTADE_OBJECT_GENERATOR(range_based1, (range_based1_return_op< deduce<_1, as_value> >))


} } } // namespace pstade::oven::detail


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, class Range0, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, Range0, BOOST_PP_ENUM_PARAMS(n, A)> :
    result_of<
        IterBased const(
            typename range_iterator<Range0>::type const&,
            typename range_iterator<Range0>::type const&,
            PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
        )
    >
{ };

template< class Result, class Range0, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(Range0& rng0, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(
        to_cref(boost::begin(rng0)),
        to_cref(boost::end(rng0)),
        BOOST_PP_ENUM_PARAMS(n, a)
    );
}


#undef n
#endif
