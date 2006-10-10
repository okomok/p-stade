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


namespace pstade { namespace oven {

PSTADE_ADL_BARRIER(numeric) {


template< class Range, class T > inline
T accumulate(Range const& rng, T const& init)
{
    return std::accumulate(boost::begin(rng), boost::end(rng), init);
}

template< class Range, class T, class BinaryOp > inline
T accumulate(Range const& rng, T const& init, BinaryOp op)
{
    return std::accumulate(boost::begin(rng), boost::end(rng), init, op);
}


template< class Range1, class Iterator2, class T > inline
T inner_product(Range1 const& rng1, Iterator2 const& first2, T const& init)
{
    return std::inner_product(boost::begin(rng1), boost::end(rng1), first2, init);
}

template< class Range1, class Iterator2, class T, class BinaryOp1, class BinaryOp2 > inline
T inner_product(Range1 const& rng1, Iterator2 const& first2, T const& init, BinaryOp1 op1, BinaryOp2 op2)
{
    return std::inner_product(boost::begin(rng1), boost::end(rng1), first2, init, op1, op2);
}


template< class Range, class OutIter >
OutIter partial_sum(Range const& rng, OutIter const& result)
{
    return std::partial_sum(boost::begin(rng), boost::end(rng), result);
}

template< class Range, class OutIter, class BinaryOp >
OutIter partial_sum(Range const& rng, OutIter const& result, BinaryOp op)
{
    return std::partial_sum(boost::begin(rng), boost::end(rng), result, op);
}


template< class Range, class OutIter >
OutIter adjacent_difference(Range const& rng, OutIter const& result)
{
    return std::adjacent_difference(boost::begin(rng), boost::end(rng), result);
}

template< class Range, class OutIter, class BinaryOp >
OutIter adjacent_difference(Range const& rng, OutIter const& result, BinaryOp op)
{
    return std::adjacent_difference(boost::begin(rng), boost::end(rng), result, op);
}


} // ADL barrier

} } // namespace pstade::oven


#endif
