#ifndef PSTADE_OVEN_MERGE_RANGE_HPP
#define PSTADE_OVEN_MERGE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./merge_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace merge_range_detail {


    template<
        class Range1, class Range2,
        class Compare,
        class MergeRoutine
    >
    struct super_ :
        iter_range<
            merge_iterator<
                typename range_iterator<Range1>::type,
                typename range_iterator<Range2>::type,
                Compare,
                MergeRoutine
            >
        >
    { };


} // namespace merge_range_detail


template<
    class Range1, class Range2,
    class Compare      = op_less,
    class MergeRoutine = merge_iterator_detail::merge_routine
>
struct merge_range :
    merge_range_detail::super_<Range1, Range2, Compare, MergeRoutine>::type,
    private as_lightweight_proxy< merge_range<Range1, Range2, Compare, MergeRoutine> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range1>));
    PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range2>));
    typedef merge_range type;
    typedef Compare compare_type;

private:
    typedef typename merge_range_detail::super_<Range1, Range2, Compare, MergeRoutine>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    merge_range(Range1& rng1, Range2& rng2, Compare const& comp = pstade::less) :
        super_t(
            iter_t(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2), comp),
            iter_t(boost::end(rng1),   boost::end(rng1), boost::end(rng2),   boost::end(rng2), comp)
        )
    { }

    typedef Range1 pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_merge_range,
    (merge_range< deduce<_1, to_qualified>, deduce<_2, to_qualified>, deduce<_3, to_value, op_less> >) const)
PSTADE_PIPABLE(merged, (op_make_merge_range))


} } // namespace pstade::oven


#endif
