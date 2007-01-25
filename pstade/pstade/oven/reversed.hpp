#ifndef PSTADE_OVEN_REVERSED_HPP
#define PSTADE_OVEN_REVERSED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


namespace reversed_detail {


    template< class Range >
    struct baby
    {
        typedef
            reverse_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            return result(boost::end(rng), boost::begin(rng)); // take care of the order!
        }
    };


} // namespace reversed_detail


PSTADE_FUNCTION(make_reversed, (reversed_detail::baby<_>))
PSTADE_PIPABLE(reversed, (op_make_reversed))


} } // namespace pstade::oven


#endif
