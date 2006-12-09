#ifndef PSTADE_OVEN_ADJACENT_FILTER_RANGE_HPP
#define PSTADE_OVEN_ADJACENT_FILTER_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./adjacent_filter_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace adjacent_filter_range_detail {


    template< class Range, class BinaryPred >
    struct super_ :
        iter_range<
            adjacent_filter_iterator<
                typename range_iterator<Range>::type,
                BinaryPred
            >
        >
    { };


} // namespace adjacent_filter_range_detail


template< class Range, class BinaryPred >
struct adjacent_filter_range :
    adjacent_filter_range_detail::super_<Range, BinaryPred>::type,
    private as_lightweight_proxy< adjacent_filter_range<Range, BinaryPred> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef BinaryPred predicate_type;

private:
    typedef typename adjacent_filter_range_detail::super_<Range, BinaryPred>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    adjacent_filter_range(Range& rng, BinaryPred const& pred) :
        super_t(
            iter_t(boost::begin(rng), pred, boost::begin(rng), boost::end(rng)),
            iter_t(boost::end(rng),   pred, boost::begin(rng), boost::end(rng))
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_adjacent_filter_range, adjacent_filter_range, 2, (object_by_qualifier))
PSTADE_PIPABLE(adjacent_filtered, op_make_adjacent_filter_range)


} } // namespace pstade::oven


#endif
