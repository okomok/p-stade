#ifndef PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP


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
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./adjacent_transform_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace adjacent_transform_range_detail {


    template< class Range, class BinaryFun, class Reference, class Value >
    struct super_ :
        iter_range<
            adjacent_transform_iterator<
                typename range_iterator<Range>::type,
                BinaryFun, Reference, Value
            >
        >
    { };


} // namespace adjacent_transform_range_detail


template<
    class Range,
    class BinaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct adjacent_transform_range :
    adjacent_transform_range_detail::super_<Range, BinaryFun, Reference, Value>::type,
    private as_lightweight_proxy< adjacent_transform_range<Range, BinaryFun, Reference, Value> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef adjacent_transform_range type;
    typedef BinaryFun function_type;

private:
    typedef typename adjacent_transform_range_detail::super_<Range, BinaryFun, Reference, Value>::type super_t;

public:
    adjacent_transform_range(Range& rng, BinaryFun const& fun) :
        super_t(
            oven::make_adjacent_transform_begin_iterator<Reference, Value>(boost::begin(rng), boost::end(rng), fun),
            oven::make_adjacent_transform_end_iterator  <Reference, Value>(boost::begin(rng), boost::end(rng), fun)
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_adjacent_transform_range, const(adjacent_transform_range< deduce_to_qualified<from_1>, deduce_to_value<from_2> >))
PSTADE_PIPABLE(adjacent_transformed, (op_make_adjacent_transform_range))


} } // namespace pstade::oven


#endif
