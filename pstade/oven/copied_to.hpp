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
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace copied_to_detail {


    struct baby
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


    typedef egg::function<baby> op;


} // namespace copied_to_detail


PSTADE_POD_CONSTANT((egg::result_of_pipable<copied_to_detail::op>::type), copied_to)
    = PSTADE_EGG_PIPABLE({{}} BOOST_PP_EMPTY)();


} } // namespace pstade::oven


#endif
