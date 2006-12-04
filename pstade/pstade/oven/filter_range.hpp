#ifndef PSTADE_OVEN_FILTER_RANGE_HPP
#define PSTADE_OVEN_FILTER_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace filter_range_detail {


    template< class Range, class Predicate >
    struct super_ :
        iter_range<
            boost::filter_iterator<
                Predicate,
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace filter_range_detail


template< class Range, class Predicate >
struct filter_range :
    filter_range_detail::super_<Range, Predicate>::type,
    private as_lightweight_proxy< filter_range<Range, Predicate> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef Predicate predicate_type;

private:
    typedef typename filter_range_detail::super_<Range, Predicate>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    filter_range(Range& rng, Predicate const& pred) :
        super_t(
            iter_t(pred, boost::begin(rng), boost::end(rng)),
            iter_t(pred, boost::end(rng),   boost::end(rng))
        )
    { }

    predicate_type const predicate() const
    {
        return this->begin().predicate();
    }

    typedef Range pstade_oven_range_base_type;
};


namespace filter_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Predicate >
        struct apply
        {
            typedef typename pass_by_value<Predicate>::type pred_t;
            typedef filter_range<Range, pred_t> const type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate& pred) const
        {
            return Result(rng, pred);
        }
    };


} // namespace filter_range_detail


PSTADE_EGG_FUNCTION(make_filter_range, filter_range_detail::baby_make)
PSTADE_PIPABLE(filtered, make_filter_range_fun)


} } // namespace pstade::oven


#endif
