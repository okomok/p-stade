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
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/config.hpp> // PSTADE_EGG_MAX_ARITY
#include <pstade/egg/function.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/egg/sig_template.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/egg/use_brace_level1.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../range_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IterBased >
struct baby_range_based1_result
{
    IterBased m_base;

    typedef IterBased base_type;

    IterBased base() const
    {
        return m_base;
    }

    template< class Myself, class Range0, PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_MAX_ARITY, class A, = void) >
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
        return m_base(
            egg::to_cref(boost::begin(rng0)),
            egg::to_cref(boost::end(rng0))
        );
    }

    // rng0 + 1ary-
#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/oven/detail/range_based1.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity

    #include PSTADE_EGG_SIG_TEMPLATE()
};


template< class IterBased >
struct result_of_range_based1
{
    typedef egg::function< baby_range_based1_result<IterBased> > type;
};


#define PSTADE_OVEN_RANGE_BASED1(B) \
    { { B() } } BOOST_PP_EMPTY \
/**/


typedef
    egg::generator<
        result_of_range_based1< egg::deduce<boost::mpl::_1, egg::as_value> >::type,
        egg::use_brace_level1
    >::type
op_range_based1;

PSTADE_POD_CONSTANT((op_range_based1), range_based1) = PSTADE_EGG_GENERATOR_TYPE();


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
        return m_base(
            egg::to_cref(boost::begin(rng0)),
            egg::to_cref(boost::end(rng0)),
            BOOST_PP_ENUM_PARAMS(n, a)
        );
    }


#undef n
#endif
