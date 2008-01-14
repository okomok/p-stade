#ifndef PSTADE_OVEN_OFFSET_HPP
#define PSTADE_OVEN_OFFSET_HPP
#include "./detail/prefix.hpp"


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
#include "./advance_from.hpp"
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./traversal_tags.hpp" // is_bidirectional, is_random_access


namespace pstade { namespace oven {


namespace offset_detail {


    template< class Range >
    struct base
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Range& rng, diff_t n1, diff_t n2) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(is_random_access(rng) ? n1 <= distance(rng) + n2 : true);
            BOOST_ASSERT(n1 < 0 ? is_bidirectional(rng) : true);
            BOOST_ASSERT(n2 < 0 ? is_bidirectional(rng) : true);

            return result_type(
                advance_from(boost::begin(rng), n1),
                advance_from(boost::end(rng),   n2)
            );
        }
    };


} // namespace offset_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(offset, (offset_detail::base<_>))


} } // namespace pstade::oven


#endif
