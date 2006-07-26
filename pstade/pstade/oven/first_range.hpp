#ifndef PSTADE_OVEN_FIRST_RANGE_HPP
#define PSTADE_OVEN_FIRST_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/argument.hpp"
#include "./detail/concept_check.hpp"
#include "./detail/propagate.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace first_range_detail {


    template< class PairRange >
    struct get_first
    {
        typedef typename range_reference<PairRange>::type pair_ref_t;
        typedef typename range_value<PairRange>::type pair_t;

        typedef typename detail::propagate<
            pair_ref_t,
            typename pair_t::first_type
        >::type result_type;

        typedef typename detail::argument<pair_ref_t>::type arg_t;
        result_type operator()(arg_t p) const
        {
            return p.first;
        }
    };


    template< class PairRange >
    struct super_
    {
        typedef boost::iterator_range<
            boost::transform_iterator<
                get_first<PairRange>,
                typename range_iterator<PairRange>::type
            >
        > type;
    };


} // namespace first_range_detail


template< class PairRange >
struct first_range :
    first_range_detail::super_<PairRange>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(PairRange, SinglePassRangeConcept);
    typedef typename first_range_detail::super_<PairRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit first_range(PairRange& rng) :
    super_t(
        iter_t(boost::begin(rng), first_range_detail::get_first<PairRange>()),
        iter_t(boost::end(rng), first_range_detail::get_first<PairRange>())
    )
    { }
};


namespace first_range_detail {


    struct baby_generator
    {
        template< class Unused, class PairRange >
        struct result
        {
            typedef first_range<PairRange> const type;
        };

        template< class Result, class PairRange >
        Result call(PairRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace first_range_detail


PSTADE_EGG_FUNCTION(make_first_range, first_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(firsts, first_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::first_range, 1)


#endif
