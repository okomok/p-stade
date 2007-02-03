#ifndef PSTADE_OVEN_FOUND_HPP
#define PSTADE_OVEN_FOUND_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./find_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace found_detail {


    template< class Range, class Finder >
    struct baby
    {
        typedef
            find_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Finder>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, Finder& finder)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));

            return result(
               iter_t(boost::begin(rng), finder, boost::end(rng)),
               iter_t(boost::end(rng),   finder, boost::end(rng))
            );
        }
    };


} // namespace found_detail


PSTADE_FUNCTION(make_found, (found_detail::baby<_, _>))
PSTADE_PIPABLE(found, (op_make_found))


} } // namespace pstade::oven


#endif
