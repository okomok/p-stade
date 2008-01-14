#ifndef PSTADE_OVEN_DROPPED_WHILE_HPP
#define PSTADE_OVEN_DROPPED_WHILE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Differently from 'taken_while', this adaptor is not lazy.
// I can't imagine the benefit of something like 'drop_while_iterator'.
// With such iterator, an expression:
// 'counting(1, 10^10)|identities(in_forward)|dropped(10^10 - 1)|reversed;'
// won't hang up. But once you call 'copy', it is inevitable to hang up.
// After all, this behavior follows 'boost::filter_iterator'.


#include <algorithm> // find_if
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/not.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace dropped_while_detail {


    template< class Range >
    struct base
    {
        typedef typename
            iter_range_of<Range>::type const
        result_type;

        template< class Predicate >
        result_type operator()(Range& rng, Predicate pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return aux(boost::begin(rng), boost::end(rng), pred);
        }

        template< class Iterator, class Predicate >
        result_type aux(Iterator first, Iterator last, Predicate pred) const
        {
            return result_type(std::find_if(first, last, egg::not_(pred)), last);
        }
    };


} // namespace dropped_while_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(dropped_while, (dropped_while_detail::base<_>))


} } // namespace pstade::oven


#endif
