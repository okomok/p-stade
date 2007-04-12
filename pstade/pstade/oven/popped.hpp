#ifndef PSTADE_OVEN_POPPED_HPP
#define PSTADE_OVEN_POPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This never accepts an empty range --
// following Container and Haskell's 'init'.


#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace popped_detail {


    namespace here = popped_detail;


    template< class ForwardIter > inline
    ForwardIter prior_of_end_aux(ForwardIter first, ForwardIter last,
        boost::bidirectional_traversal_tag)
    {
        unused(first);
        return boost::prior(last);
    }

    template< class ForwardIter >
    ForwardIter prior_of_end_aux(ForwardIter first, ForwardIter last,
        boost::forward_traversal_tag)
    {
        ForwardIter prev(first);
        for (; ++first != last; prev = first)
            ;

        return prev;
    }


    template< class ForwardIter > inline
    ForwardIter prior_of_end(ForwardIter first, ForwardIter last)
    {
        return here::prior_of_end_aux(first, last,
            typename boost::iterator_traversal<ForwardIter>::type());
    }


    template< class Range >
    struct baby
    {
        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(!boost::empty(rng));

            return result_type(
                boost::begin(rng),
                here::prior_of_end(boost::begin(rng), boost::end(rng))
            );
        }
    };


} // namespace popped_detail


PSTADE_FUNCTION(make_popped, (popped_detail::baby<_>))
PSTADE_PIPABLE(popped, (op_make_popped))


} } // namespace pstade::oven


#endif
