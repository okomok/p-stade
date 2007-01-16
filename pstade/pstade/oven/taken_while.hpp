#ifndef PSTADE_OVEN_TAKEN_WHILE_HPP
#define PSTADE_OVEN_TAKEN_WHILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // not_
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // find_if
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"
#include "./take_while_iterator.hpp"


namespace pstade { namespace oven {


namespace taken_while_detail {


    template< class Result, class Range, class Predicate > inline
    Result aux(Range& rng, Predicate& pred, boost::forward_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        return Result(
            boost::begin(rng),
            find_if(rng, not_(pred))
        );
    }

    template< class Result, class Range, class Predicate > inline
    Result aux(Range& rng, Predicate& pred, boost::single_pass_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), pred),
            iter_t(boost::end(rng),   boost::end(rng), pred)
        );
    }


    template< class Range, class Predicate >
    struct baby
    {
        typedef typename
            boost::mpl::eval_if<
                boost::is_convertible<
                    typename range_traversal<Range>::type,
                    boost::forward_traversal_tag
                >,
                range_iterator<Range>,
                boost::mpl::identity<
                    take_while_iterator<
                        typename range_iterator<Range>::type,
                        typename pass_by_value<Predicate>::type
                    >
                >
            >::type
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, Predicate& pred)
        {
            return taken_while_detail::aux<result>(rng, pred, typename range_traversal<Range>::type());
        }
    };


} // namespace taken_while_detail


PSTADE_FUNCTION(make_taken_while, (taken_while_detail::baby<_, _>))
PSTADE_PIPABLE(taken_while, (op_make_taken_while))


} } // namespace pstade::oven


#endif
