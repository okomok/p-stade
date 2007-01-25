#ifndef PSTADE_OVEN_CYCLED_HPP
#define PSTADE_OVEN_CYCLED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./cycle_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace cycled_detail {


    template< class Range, class Size >
    struct baby
    {
        typedef
            cycle_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Size>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, Size& sz)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
    
            return result(
                iter_t(boost::begin(rng), 0,  boost::begin(rng), boost::end(rng)),
                iter_t(boost::begin(rng), sz, boost::begin(rng), boost::end(rng))
            );
        }
    };


} // namespace cycled_detail


PSTADE_FUNCTION(make_cycled, (cycled_detail::baby<_, _>))
PSTADE_PIPABLE(cycled, (op_make_cycled))


} } // namespace pstade::oven


#endif
