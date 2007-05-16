#ifndef PSTADE_OVEN_APPENDED_HPP
#define PSTADE_OVEN_APPENDED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
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


namespace appended_detail {


    template< class Range, class Value >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_jointed(Range&, typename boost::result_of<op_single(Value&)>::type)
            >::type
        result_type;

        result_type operator()(Range& rng, Value& v) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return make_jointed(rng, single(v));
        }
    };


} // namespace appended_detail


PSTADE_FUNCTION(make_appended, (appended_detail::baby<_, _>))
PSTADE_PIPABLE(appended, (op_make_appended))


} } // namespace pstade::oven


#endif
