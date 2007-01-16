#ifndef PSTADE_OVEN_TRANSFORMED_HPP
#define PSTADE_OVEN_TRANSFORMED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Boost.Iterator doesn't use 'result_of'.
// 'result_of' seems to have many problems
// even under modern compilers. But we must go!


// Note:
//
// Consider the following simple functor.
//
// struct id
// {
//     typedef int const& result_type;
//     result_type operator()(int const& x) const
//     { return x; }
// };
//
// A transformed range whose 'reference' is 'int'(non-reference)
// cannot work with this functor because of dangling reference.
// A transformed range's 'reference' type is sometimes
// orthogonal to functor's 'result_type'.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_make_transformed :
    callable< op_make_transformed<Reference, Value> >
{
    template< class Myself, class Range, class UnaryFun >
    struct apply
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename range_iterator<Range>::type base_iter_t;
        typedef typename pass_by_value<UnaryFun>::type fun_t;

        typedef typename
            boost::iterator_reference<base_iter_t>::type
        base_ref_t;

        typedef typename
            use_default_eval_to<
                Reference,
                boost::result_of<fun_t(base_ref_t)>
            >::type
        ref_t;

        typedef
            iter_range<
                boost::transform_iterator<
                    fun_t, base_iter_t, ref_t, Value
                >
            > const
        type;
    };

    template< class Result, class Range, class UnaryFun >
    Result call(Range& rng, UnaryFun& fun) const
    {
        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), fun),
            iter_t(boost::end(rng),   fun)
        );
    }
};


PSTADE_CONSTANT(make_transformed, (op_make_transformed<>))
PSTADE_PIPABLE(transformed, (op_make_transformed<>))


} } // namespace pstade::oven


#endif
