#ifndef PSTADE_OVEN_SLICED_HPP
#define PSTADE_OVEN_SLICED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./slice_iterator.hpp"


namespace pstade { namespace oven {


namespace sliced_detail {


    template< class Range, class Difference > inline
    bool is_sliceable_with(Range& rng, Difference const& stride)
    {
        Difference d = distance(rng);
        return d == 0 || d % stride == 0;
    }


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef
            slice_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, diff_t const& start, diff_t const& stride)
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));

            // 'rng' can be infinite?
        #if defined(PSTADE_OVEN_SLICED_DEBUG_IS_SLICEABLE)
            BOOST_ASSERT((is_sliceable_with)(rng, stride));
        #endif

            return result(
                iter_t(boost::begin(rng), start, stride),
                iter_t(boost::end(rng),   start, stride)
            );
        }
    };


} // namespace sliced_detail


PSTADE_FUNCTION(make_sliced, (sliced_detail::baby<_, _, _>))
PSTADE_PIPABLE(sliced, (op_make_sliced))


} } // namespace pstade::oven


#endif
