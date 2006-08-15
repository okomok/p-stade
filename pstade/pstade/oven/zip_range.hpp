#ifndef PSTADE_OVEN_ZIP_RANGE_HPP
#define PSTADE_OVEN_ZIP_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace zip_range_detail {


    template< class Range0, class Range1 >
    struct iterator_tuple
    {
        typedef typename range_iterator<Range0>::type iter0_t;
        typedef typename range_iterator<Range1>::type iter1_t;
        typedef boost::tuples::tuple<iter0_t, iter1_t> type;
    };


    template< class Range0, class Range1 >
    struct super_
    {
        typedef boost::iterator_range<
            boost::zip_iterator<
                typename iterator_tuple<Range0, Range1>::type
            >
        > type;
    };


} // namespace zip_range_detail


template< class Range0, class Range1 >
struct zip_range :
    zip_range_detail::super_<Range0, Range1>::type,
    private lightweight_proxy< zip_range<Range0, Range1> >
{
    typedef Range0 pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range0, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range1, SinglePassRangeConcept);
    typedef typename zip_range_detail::super_<Range0, Range1>::type super_t;

public:
    zip_range(Range0& rng0, Range1& rng1) :
        super_t(
            boost::tuples::make_tuple(boost::begin(rng0), boost::begin(rng1)),
            boost::tuples::make_tuple(boost::end(rng0), boost::end(rng1))
        )
    { }
};


namespace zip_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range0, class Range1 >
        struct result
        {
            typedef zip_range<Range0, Range1> const type;
        };

        template< class Result, class Range0, class Range1 >
        Result call(Range0& rng0, Range1& rng1)
        {
            return Result(rng0, rng1);
        }
    };


} // namespace zip_range_detail


PSTADE_EGG_FUNCTION(make_zip_range, zip_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(zipped, zip_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
