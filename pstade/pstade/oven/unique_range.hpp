#ifndef PSTADE_OVEN_UNIQUE_RANGE_HPP
#define PSTADE_OVEN_UNIQUE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/functional.hpp> // equal_to, not_
#include <pstade/pipable.hpp>
#include "./adjacent_filter_range.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"


namespace pstade { namespace oven {


namespace unique_range_detail {


    template< class Range >
    struct super_
    {
        typedef adjacent_filter_range<
            Range,
            typename boost::result_of<not_fun(equal_to_fun const&)>::type
        > type;
    };


} // namespace unique_range_detail


template< class Range >
struct unique_range :
    unique_range_detail::super_<Range>::type,
    private as_lightweight_proxy< unique_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename unique_range_detail::super_<Range>::type super_t;
    typedef typename super_t::predicate_type pred_t;

public:
    explicit unique_range(Range& rng) :
        super_t(rng, pred_t())
    { }
};


namespace unique_range_detail {


    struct baby_make
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef unique_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return Result(rng);
        }
    };


} // namespace unique_range_detail


PSTADE_EGG_FUNCTION(make_unique_range, unique_range_detail::baby_make)
PSTADE_PIPABLE(uniqued, make_unique_range_fun)


} } // namespace pstade::oven


#endif
