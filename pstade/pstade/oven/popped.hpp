#ifndef PSTADE_OVEN_POPPED_HPP
#define PSTADE_OVEN_POPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'rng|applied(pop);' is better?
// But Haskell provides one named 'init' as primitive.


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // prior
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace popped_detail {


    template< class ForwardIter > inline
    ForwardIter prior_aux(ForwardIter first, ForwardIter const& last,
        boost::bidirectional_traversal_tag)
    {
        unused(first);
        return detail::prior(last);
    }

    template< class ForwardIter >
    ForwardIter prior_aux(ForwardIter first, ForwardIter const& last,
        boost::forward_traversal_tag)
    {
        ForwardIter prev(first);
        for (; ++first != last; prev = first)
            ;

        return prev;
    }


    template< class ForwardIter > inline
    ForwardIter prior(ForwardIter const& first, ForwardIter const& last)
    {
        return (prior_aux)(first, last,
            typename boost::iterator_traversal<ForwardIter>::type());
    }


    template< class Range >
    struct baby
    {
        typedef typename
            sub_range_result<Range>::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            return result(
                boost::begin(rng),
                (prior)(boost::begin(rng), boost::end(rng))
            );
        }
    };


} // namespace popped_detail


PSTADE_FUNCTION(make_popped, (popped_detail::baby<_>))
PSTADE_PIPABLE(popped, (op_make_popped))


} } // namespace pstade::oven


#endif
