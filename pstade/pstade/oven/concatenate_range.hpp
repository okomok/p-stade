#ifndef PSTADE_OVEN_CONCATENATE_RANGE_HPP
#define PSTADE_OVEN_CONCATENATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concatenate_iterator.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace concatenate_range_detail {


    template< class TopRange >
    struct super_
    {
        typedef boost::iterator_range<
            concatenate_iterator<
                typename range_iterator<TopRange>::type
            >
        > type;
    };


} // namespace concatenate_range_detail


template< class TopRange >
struct concatenate_range :
    concatenate_range_detail::super_<TopRange>::type,
    private as_lightweight_proxy< concatenate_range<TopRange> >
{
    typedef TopRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(TopRange, SinglePassRangeConcept);
    typedef typename concatenate_range_detail::super_<TopRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit concatenate_range(TopRange& rngs) :
        super_t(
            iter_t(boost::begin(rngs), boost::end(rngs)),
            iter_t(boost::end(rngs),   boost::end(rngs))
        )
    { }
};


namespace concatenate_range_detail {


    struct baby_generator
    {
        template< class Unused, class TopRange >
        struct result
        {
            typedef concatenate_range<TopRange> const type;
        };

        template< class Result, class TopRange >
        Result call(TopRange& rngs)
        {
            return Result(rngs);
        }
    };


} // namespace concatenate_range_detail


PSTADE_EGG_FUNCTION(make_concatenate_range, concatenate_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(concatenated, concatenate_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
