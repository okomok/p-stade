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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/as.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/lambda_result_of.hpp> // inclusion guaranteed
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace range_based_detail {


    template< class IterBased, class Range >
    struct op_result :
        callable<
            op_result<IterBased, Range>,
            typename boost::result_of<
                IterBased(
                    typename range_iterator<Range>::type const&,
                    typename range_iterator<Range>::type const&
                )
            >::type   
        >
    {
        template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
        struct apply
        { }; // complete for SFINAE.

        // 0ary
        template< class Result >
        Result call() const
        {
            return m_fun(
                as_cref(boost::begin(*m_prng)),
                as_cref(boost::end(*m_prng))
            );
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/range_based.hpp>))
        #include BOOST_PP_ITERATE()

        explicit op_result()
        { }

        explicit op_result(IterBased const& fun, Range& rng) :
            m_fun(fun), m_prng(boost::addressof(rng))
        { }

        typedef IterBased base_type;

        IterBased const& base() const
        {
            return m_fun;
        }

    private:
        IterBased m_fun;
        Range *m_prng;
    };


} // namespace range_based_detail


template< class SigFun = void >
struct op_range_based :
    callable< op_range_based<SigFun> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            range_based_detail::op_result<
                typename boost::lambda::as_lambda_functor<SigFun>::type,
                Range
            >
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(
            boost::lambda::to_lambda_functor(SigFun()),
            rng
        );
    }
};


template< class SigFun, class Range > inline
typename boost::result_of<op_range_based<SigFun>(Range& rng)>::type
range_based(Range& rng PSTADE_CONST_OVERLOADED(Range))
{
    return op_range_based<SigFun>()(rng);
}

template< class SigFun, class Range > inline
typename boost::result_of<op_range_based<SigFun>(PSTADE_DEDUCED_CONST(Range)& rng)>::type
range_based(Range const& rng)
{
    return op_range_based<SigFun>()(rng);
}


template< >
struct op_range_based<> :
    callable< op_range_based<> >
{
    template< class Myself, class IterBased, class Range >
    struct apply
    {
        typedef
            range_based_detail::op_result<
                typename pass_by_value<IterBased>::type,
                Range
            >
        type;
    };

    template< class Result, class IterBased, class Range >
    Result call(IterBased& fun, Range& rng) const
    {
        return Result(fun, rng);
    }
};


template< class IterBased, class Range > inline
typename boost::result_of<op_range_based<>(IterBased&, Range& rng)>::type
range_based(IterBased fun, Range& rng)
{
    return op_range_based<>()(fun, rng);
}

template< class IterBased, class Range > inline
typename boost::result_of<op_range_based<>(IterBased&, PSTADE_DEDUCED_CONST(Range)& rng)>::type
range_based(IterBased fun, Range const& rng)
{
    return op_range_based<>()(fun, rng);
}


} } // namespace pstade::oven


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(oven)(range_based_detail)(op_result), 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<
        IterBased(
            typename range_iterator<Range>::type const&,
            typename range_iterator<Range>::type const&,
            PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
        )
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(
        as_cref(boost::begin(*m_prng)),
        as_cref(boost::end(*m_prng)),
        BOOST_PP_ENUM_PARAMS(n, a)
    );
}


#undef n
#endif
