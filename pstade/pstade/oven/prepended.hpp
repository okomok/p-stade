#ifndef PSTADE_OVEN_PREPENDED_HPP
#define PSTADE_OVEN_PREPENDED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./jointed.hpp"
#include "./single.hpp"


namespace pstade { namespace oven {


namespace prepended_detail {


    template< class Range, class Value >
    struct baby_make_prepended
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename
            boost::result_of<
                op_make_jointed(typename boost::result_of<op_make_single(Value&)>::type, Range&)
            >::type
        result;

        result call(Range& rng, Value& v)
        {
            return make_jointed(make_single(v), rng);
        }
    };


} // namespace prepended_detail


PSTADE_FUNCTION(make_prepended, (prepended_detail::baby<_, _>))
PSTADE_PIPABLE(prepended, (op_make_prepended))


} } // namespace pstade::oven


#endif
