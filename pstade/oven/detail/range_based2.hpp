#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED2_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED2_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/config.hpp> // PSTADE_EGG_MAX_ARITY
#include <pstade/egg/function.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/egg/sig_template.hpp>
#include <pstade/egg/use_brace2.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../range_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IterBased >
struct baby_range_based2_result
{
    IterBased m_base;

    typedef IterBased base_type;

    IterBased base() const
    {
        return m_base;
    }

    template< class Myself, class Range0, class Range1, PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_MAX_ARITY, class A, = void) >
    struct apply
    { }; // complete for msvc warning.

    // rng0 + rng1 + 0ary
    template< class Myself, class Range0, class Range1 >
    struct apply<Myself, Range0, Range1> :
        result_of<
            IterBased const(
                typename range_iterator<Range0>::type,
                typename range_iterator<Range0>::type,
                typename range_iterator<Range1>::type,
                typename range_iterator<Range1>::type
            )
        >
    { };

    template< class Result, class Range0, class Range1 >
    Result call(Range0& rng0, Range1& rng1) const
    {
        return m_base(
            boost::begin(rng0),
            boost::end(rng0),
            boost::begin(rng1),
            boost::end(rng1)
        );
    }

    // rng0 + rng1 + 1ary-
#define PSTADE_max_arity BOOST_PP_DEC(BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY))
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/oven/detail/range_based2.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity

    #include PSTADE_EGG_SIG_TEMPLATE()
};


template< class IterBased >
struct result_of_range_based2
{
    typedef
        egg::function< baby_range_based2_result<IterBased> >
    type;
};


#define PSTADE_OVEN_RANGE_BASED2_L { {
#define PSTADE_OVEN_RANGE_BASED2_R } }
#define PSTADE_OVEN_RANGE_BASED2(F) PSTADE_OVEN_RANGE_BASED2_L F PSTADE_OVEN_RANGE_BASED2_R


typedef
    egg::generator<
        result_of_range_based2< egg::deduce<boost::mpl::_1, egg::as_value> >::type,
        boost::use_default,
        egg::use_brace2,
        egg::by_value
    >::type
T_range_based2;

PSTADE_POD_CONSTANT((T_range_based2), range_based2) = PSTADE_EGG_GENERATOR;


} } } // namespace pstade::oven::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template< class Myself, class Range0, class Range1, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct apply<Myself, Range0, Range1, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            IterBased const(
                typename range_iterator<Range0>::type,
                typename range_iterator<Range0>::type,
                typename range_iterator<Range1>::type,
                typename range_iterator<Range1>::type,
                PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
            )
        >
    { };

    template< class Result, class Range0, class Range1, BOOST_PP_ENUM_PARAMS(n, class A) >
    Result call(Range0& rng0, Range1& rng1, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(
            boost::begin(rng0),
            boost::end(rng0),
            boost::begin(rng1),
            boost::end(rng1),
            BOOST_PP_ENUM_PARAMS(n, a)
        );
    }


#undef n
#endif
