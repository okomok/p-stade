#ifndef PSTADE_OVEN_DIRECTED_HPP
#define PSTADE_OVEN_DIRECTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./counting.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace directed_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            range_iterator<Range>::type
        iter_t;

        typedef typename
            boost::result_of<
                op_counting<>(iter_t, iter_t)
            >::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return counting(boost::begin(rng), boost::end(rng));
        }
    };


} // namespace directed_detail


PSTADE_FUNCTION(make_directed, (directed_detail::baby<_>))
PSTADE_PIPABLE(directed, (op_make_directed))


} } // namespace pstade::oven


#endif
