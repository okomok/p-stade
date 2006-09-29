#ifndef PSTADE_OVEN_NULL_TERMINATE_RANGE_HPP
#define PSTADE_OVEN_NULL_TERMINATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // not_, is_zero
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./take_while_range.hpp"


namespace pstade { namespace oven {


template< class ForwardRange >
bool is_null_terminated(ForwardRange const& rng)
{
    detail::requires< boost::ForwardRangeConcept<ForwardRange> >();

    typedef typename range_iterator_const<ForwardRange>::type iter_t;

    iter_t first = boost::begin(rng);
    iter_t last = boost::end(rng);
    iter_t it = std::find(first, last, 0);

    return it != last;
}


template< class ForwardRange > inline
void null_terminate(ForwardRange& rng)
{
    BOOST_ASSERT(!boost::empty(rng));
    *boost::begin(rng) = 0;
}


namespace null_terminate_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef take_while_range<
            ForwardRange,
            typename boost::result_of<not_fun(is_zero_fun)>::type
        > type;
    };


} // namespace null_terminate_range_detail



template< class ForwardRange >
struct null_terminate_range :
    null_terminate_range_detail::super_<ForwardRange>::type,
    /*private, which VC7.1 complains about*/ as_lightweight_proxy< null_terminate_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeRangeConcept);
    typedef typename null_terminate_range_detail::super_<ForwardRange>::type super_t;
    typedef typename super_t::predicate_type pred_t;

public:
    explicit null_terminate_range(ForwardRange& rng) :
        super_t(rng, pred_t())
    {
        BOOST_ASSERT(oven::is_null_terminated(rng));
    }
};


namespace null_terminate_range_detail {


    struct baby_make
    {
        template< class Unused, class ForwardRange >
        struct apply
        {
            typedef null_terminate_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace null_terminate_range_detail


PSTADE_EGG_FUNCTION(make_null_terminate_range, null_terminate_range_detail::baby_make)
PSTADE_EGG_PIPABLE(null_terminated, null_terminate_range_detail::baby_make)


} } // namespace pstade::oven


#endif
