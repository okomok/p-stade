#ifndef PSTADE_OVEN_FILTERED_HPP
#define PSTADE_OVEN_FILTERED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace filtered_detail {


    template< class Range, class Predicate >
    struct baby
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        // PSTADE_CONCEPT_ASSERT((Readable<Range>));

        typedef
            boost::filter_iterator<
                typename pass_by_value<Predicate>::type,
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, Predicate& pred)
        {
            return result(
                iter_t(pred, boost::begin(rng), boost::end(rng)),
                iter_t(pred, boost::end(rng),   boost::end(rng))
            );
        }
    };


} // namespace filtered_detail


PSTADE_FUNCTION(make_filtered, (filtered_detail::baby<_, _>))
PSTADE_PIPABLE(filtered, (op_make_filtered))


} } // namespace pstade::oven


#endif
