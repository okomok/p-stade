#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_RANGE_BASED2_HPP
#define PSTADE_OVEN_RANGE_BASED2_HPP


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
#include <boost/utility/result_of.hpp>
#include <pstade/as.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_fun.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace range_based2_detail {


    template< class IterBased >
    struct return_op :
        callable< return_op<IterBased> >
    {
        template< class Myself, class Range0, class Range1, PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_CALLABLE_MAX_ARITY, class A, = void) >
        struct apply
        { }; // complete for SFINAE.

        // rng0 + rng1 + 0ary
        template< class Myself, class Range0, class Range1 >
        struct apply<Myself, Range0, Range1> :
            boost::result_of<
                PSTADE_CONST_FUN_TPL(IterBased)(
                    typename range_iterator<Range0>::type const&,
                    typename range_iterator<Range0>::type const&,
                    typename range_iterator<Range1>::type const&,
                    typename range_iterator<Range1>::type const&
                )
            >
        { };

        template< class Result, class Range0, class Range1 >
        Result call(Range0& rng0, Range1& rng1) const
        {
            return m_fun(
                as_cref(boost::begin(rng0)),
                as_cref(boost::end(rng0)),
                as_cref(boost::begin(rng1)),
                as_cref(boost::end(rng1))
            );
        }

        // rng0 + rng1 + 1ary-
    #define PSTADE_max_arity BOOST_PP_DEC(BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/oven/range_based2.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity

        explicit return_op()
        { }

        explicit return_op(IterBased const& fun) :
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


} // namespace range_based2_detail


PSTADE_OBJECT_GENERATOR(range_based2, (range_based2_detail::return_op< deduce<_1, to_value> >))


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, class Range0, class Range1, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, Range0, Range1, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<
        PSTADE_CONST_FUN_TPL(IterBased)(
            typename range_iterator<Range0>::type const&,
            typename range_iterator<Range0>::type const&,
            typename range_iterator<Range1>::type const&,
            typename range_iterator<Range1>::type const&,
            PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
        )
    >
{ };

template< class Result, class Range0, class Range1, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(Range0& rng0, Range1& rng1, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(
        as_cref(boost::begin(rng0)),
        as_cref(boost::end(rng0)),
        as_cref(boost::begin(rng1)),
        as_cref(boost::end(rng1)),
        BOOST_PP_ENUM_PARAMS(n, a)
    );
}


#undef n
#endif
