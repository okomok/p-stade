#ifndef PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// Adjacent convenience - algorithms on adjacent pairs
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/df2bf11921c91fad/
//
// You may say this range could be implemented by 'transform_range' and 'zip_range'
// without a specific iterator. But such implementation would not be so simple.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./adjacent_transform_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_make_adjacent_transformed :
    callable< op_make_adjacent_transformed<Reference, Value> >
{
    template< class Myself, class Range, class BinaryFun >
    struct apply
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef
            adjacent_transform_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<BinaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class BinaryFun >
    Result call(Range& rng, BinaryFun& fun) const
    {
        return Result(
            oven::make_adjacent_transform_begin_iterator<Reference, Value>(boost::begin(rng), boost::end(rng), fun),
            oven::make_adjacent_transform_end_iterator  <Reference, Value>(boost::begin(rng), boost::end(rng), fun)
        );
    }
};


PSTADE_CONSTANT(make_adjacent_transformed, (op_make_adjacent_transformed<>))
PSTADE_PIPABLE(adjacent_transformed, (op_make_adjacent_transformed<>))


} } // namespace pstade::oven


#endif
