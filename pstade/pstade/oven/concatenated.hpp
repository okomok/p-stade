#ifndef PSTADE_OVEN_CONCATENATED_HPP
#define PSTADE_OVEN_CONCATENATED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concatenate_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace concatenated_detail {


    template< class SegmentRange >
    struct baby
    {
        typedef
            concatenate_iterator<
                typename range_iterator<SegmentRange>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(SegmentRange& rngs) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<SegmentRange>));
            PSTADE_CONCEPT_ASSERT((SinglePass<typename range_value<SegmentRange>::type>));

            return result_type(
                iter_t(boost::begin(rngs), boost::end(rngs)),
                iter_t(boost::end(rngs),   boost::end(rngs))
            );
        }
    };


} // namespace concatenated_detail


PSTADE_FUNCTION(make_concatenated, (concatenated_detail::baby<_>))
PSTADE_PIPABLE(concatenated, (op_make_concatenated))


} } // namespace pstade::oven


#endif
