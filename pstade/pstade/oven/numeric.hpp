#ifndef PSTADE_OVEN_NUMERIC_HPP
#define PSTADE_OVEN_NUMERIC_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <numeric>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace oven {

PSTADE_ADL_BARRIER(numeric) {


    struct op_accumulate :
        callable<op_accumulate>
    {
        template< class Myself, class Range, class T, class BinaryOp = void >
        struct apply :
            pass_by_value<T>
        { };

        template< class Result, class Range, class T >
        Result call(Range& rng, T& init) const
        {
            return std::accumulate(boost::begin(rng), boost::end(rng), init);
        }

        template< class Result, class Range, class T, class BinaryOp > inline
        Result call(Range& rng, T& init, BinaryOp& op) const
        {
            return std::accumulate(boost::begin(rng), boost::end(rng), init, op);
        }
    };

    PSTADE_CONSTANT(accumulate, (op_accumulate))


    struct op_inner_product :
        callable<op_inner_product>
    {
        template< class Myself, class Range1, class Iterator2, class T, class BinaryOp1 = void, class = void >
        struct apply :
            pass_by_value<T>
        { };

        template< class Result, class Range1, class Iterator2, class T >
        Result call(Range1& rng1, Iterator2& first2, T& init) const
        {
            return std::inner_product(boost::begin(rng1), boost::end(rng1), first2, init);
        }

        template< class Result, class Range1, class Iterator2, class T, class BinaryOp1, class BinaryOp2 >
        Result call(Range1& rng1, Iterator2& first2, T& init, BinaryOp1& op1, BinaryOp2& op2) const
        {
            return std::inner_product(boost::begin(rng1), boost::end(rng1), first2, init, op1, op2);
        }
    };

    PSTADE_CONSTANT(inner_product, (op_inner_product))


    struct op_partial_sum :
        callable<op_partial_sum>
    {
        template< class Myself, class Range, class OutIter, class BinaryOp = void >
        struct apply :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, OutIter& result_) const // VC7.1 error C2955 needs different name from 'result'.
        {
            return std::partial_sum(boost::begin(rng), boost::end(rng), result_);
        }

        template< class Result, class Range, class OutIter, class BinaryOp >
        Result call(Range& rng, OutIter& result_, BinaryOp& op) const
        {
            return std::partial_sum(boost::begin(rng), boost::end(rng), result_, op);
        }
    };

    PSTADE_CONSTANT(partial_sum, (op_partial_sum))


    struct op_adjacent_difference :
        callable<op_adjacent_difference>
    {
        template< class Myself, class Range, class OutIter, class BinaryOp = void >
        struct apply :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, OutIter& result_) const
        {
            return std::adjacent_difference(boost::begin(rng), boost::end(rng), result_);
        }

        template< class Result, class Range, class OutIter, class BinaryOp >
        Result call(Range& rng, OutIter& result_, BinaryOp& op) const
        {
            return std::adjacent_difference(boost::begin(rng), boost::end(rng), result_, op);
        }
    };

    PSTADE_CONSTANT(adjacent_difference, (op_adjacent_difference))


} // ADL barrier

} } // namespace pstade::oven


#endif
