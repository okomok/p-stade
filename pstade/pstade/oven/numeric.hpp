#ifndef PSTADE_OVEN_NUMERIC_HPP
#define PSTADE_OVEN_NUMERIC_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <numeric> // inner_product
#include <boost/lambda/numeric.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include "./detail/range_based_sig_fun.hpp"


namespace pstade { namespace oven {


#define PSTADE_numeric \
    (accumulate)(partial_sum)(adjacent_difference) \
/**/


PSTADE_ADL_BARRIER(numeric) {
    

    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_DETAIL_RANGE_BASED1_LL, ~, PSTADE_numeric)


    // The arity of 'inner_product' is too many.

    struct op_inner_product :
        callable<op_inner_product>
    {
        template< class Myself, class Range0, class InputIter1, class T, class BinaryOp0 = void, class BinaryOp1 = void >
        struct apply :
            pass_by_value<T>
        { };

        template< class Result, class Range0, class InputIter1, class T, class BinaryOp0, class BinaryOp1 >
        Result call(Range0& rng0, InputIter1& first1, T& init, BinaryOp0& op0, BinaryOp1& op1) const
        {
            return std::inner_product(boost::begin(rng0), boost::end(rng0), first1, init, op0, op1);
        }

        template< class Result, class Range0, class InputIter1, class T >
        Result call(Range0& rng0, InputIter1& first1, T& init) const
        {
            return std::inner_product(boost::begin(rng0), boost::end(rng0), first1, init);
        }
    };

    PSTADE_CONSTANT(inner_product, (op_inner_product))


} // ADL barrier


#undef  PSTADE_numeric


} } // namespace pstade::oven


#endif
