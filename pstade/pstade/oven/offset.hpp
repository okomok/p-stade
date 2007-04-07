#ifndef PSTADE_OVEN_OFFSET_HPP
#define PSTADE_OVEN_OFFSET_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range had the name 'shift_range',
// which is reserved to "logical shift operation" for someday.
// 'cshift_range'(cyclic shift operation) is also a candidate. 


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./advance.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./traversal_tags.hpp" // is_bidirectional, is_random_access


namespace pstade { namespace oven {


namespace offset_detail {


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Range& rng, diff_t const& dfirst, diff_t const& dlast) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(is_random_access(rng) ? dfirst <= distance(rng) + dlast : true);
            BOOST_ASSERT(dfirst < 0 ? is_bidirectional(rng) : true);
            BOOST_ASSERT(dlast  < 0 ? is_bidirectional(rng) : true);

	        return result_type(
                advance(boost::begin(rng), dfirst),
                advance(boost::end(rng), dlast)
            );
        }
    };


} // namespace offset_detail


PSTADE_FUNCTION(make_offset, (offset_detail::baby<_, _, _>))
PSTADE_PIPABLE(offset, (op_make_offset))


} } // namespace pstade::oven


#endif
