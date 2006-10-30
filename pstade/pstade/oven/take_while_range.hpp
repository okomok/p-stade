#ifndef PSTADE_OVEN_TAKE_WHILE_RANGE_HPP
#define PSTADE_OVEN_TAKE_WHILE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/range/begin.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // not_
#include "./algorithm.hpp" // find_if
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"
#include "./sub_range_base.hpp"
#include "./take_while_iterator.hpp"


namespace pstade { namespace oven {


namespace take_while_range_detail {


    template< class Range, class Predicate >
    struct super_ :
        boost::mpl::eval_if<
            boost::is_convertible<
                typename range_traversal<Range>::type,
                boost::forward_traversal_tag
            >,
            sub_range_base<Range>,
            iter_range<
                take_while_iterator<typename range_iterator<Range>::type, Predicate>
            >
        >
    { };


    template< class Super, class Range, class Predicate > inline
    Super make(Range& rng, Predicate const& pred, boost::forward_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        return Super(
            boost::begin(rng),
            oven::find_if(rng, pstade::not_(pred))
        );
    }

    template< class Super, class Range, class Predicate > inline
    Super make(Range& rng, Predicate const& pred, boost::single_pass_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Super::iterator iter_t;
        return Super(
            iter_t(boost::begin(rng), boost::end(rng), pred),
            iter_t(boost::end(rng),   boost::end(rng), pred)
        );
    }


} // namespace take_while_range_detail


template< class Range, class Predicate >
struct take_while_range :
    take_while_range_detail::super_<Range, Predicate>::type,
    private as_lightweight_proxy< take_while_range<Range, Predicate> >
{
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename take_while_range_detail::super_<Range, Predicate>::type super_t;
    typedef typename range_traversal<Range>::type trv_t;

public:
    take_while_range(Range& rng, Predicate const& pred) :
        super_t(take_while_range_detail::make<super_t>(rng, pred, trv_t()))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace take_while_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Predicate >
        struct apply
        {
            typedef typename pass_by_value<Predicate>::type pred_t;
            typedef take_while_range<Range, pred_t> const type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate& pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace take_while_range_detail


PSTADE_EGG_FUNCTION(make_take_while_range, take_while_range_detail::baby_make)
PSTADE_EGG_PIPABLE(taken_while, take_while_range_detail::baby_make)


} } // namespace pstade::oven


#endif
