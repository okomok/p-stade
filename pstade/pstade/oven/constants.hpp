#ifndef PSTADE_OVEN_CONSTANTS_HPP
#define PSTADE_OVEN_CONSTANTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Without a specific iterator, this could be implemented by
// using 'transformed' and 'op_identity', but 'constant_iterator' seems useful.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./constant_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace constants_detail {


    template< class Range >
    struct baby
    {
        typedef
            constant_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result(boost::begin(rng), boost::end(rng));
        }
    };


} // namespace constants_detail


PSTADE_FUNCTION(make_constants, (constants_detail::baby<_>))
PSTADE_PIPABLE(constants, (op_make_constants))


} } // namespace pstade::oven


#endif
