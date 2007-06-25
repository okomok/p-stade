#ifndef PSTADE_OVEN_COPIED_TO_HPP
#define PSTADE_OVEN_COPIED_TO_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // copy
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace copied_to_detail {


    struct op :
        callable<op>
    {
        template< class Myself, class Range, class OutIter >
        struct apply
        {
            typedef typename
                iter_range_of<Range>::type const
            type;
        };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, OutIter& out) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            std::copy(boost::begin(rng), boost::end(rng), out);
            return Result(rng);
        }
    };


} // namespace copied_to_detail


PSTADE_PIPABLE(copied_to, (copied_to_detail::op))


} } // namespace pstade::oven


#endif
