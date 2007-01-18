#ifndef PSTADE_OVEN_UNIQUED_HPP
#define PSTADE_OVEN_UNIQUED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // equal_to, not_
#include <pstade/pipable.hpp>
#include "./adjacent_filtered.hpp"
#include "./concepts.hpp"


namespace pstade { namespace oven {


namespace uniqued_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_adjacent_filtered(Range&, typename boost::result_of<op_not(op_equal_to const&)>::type)
            >::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
	        return make_adjacent_filtered(rng, not_(equal_to));
        }
    };


} // namespace uniqued_detail


PSTADE_FUNCTION(make_uniqued, (uniqued_detail::baby<_>))
PSTADE_PIPABLE(uniqued, (op_make_uniqued))


} } // namespace pstade::oven


#endif
