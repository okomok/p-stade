#ifndef PSTADE_OVEN_CHECK_RANGE_HPP
#define PSTADE_OVEN_CHECK_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./check_iterator.hpp"
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace check_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            check_iterator<
                typename range_iterator<Range>::type
            >
        > type;
    };


} // namespace check_range_detail


template< class Range >
struct check_range :
    check_range_detail::super_<Range>::type,
    private lightweight_proxy< check_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename check_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit check_range(Range& rng) :
        super_t(
            iter_t(boost::begin(rng), boost::begin(rng), boost::end(rng)),
            iter_t(boost::end(rng),   boost::begin(rng), boost::end(rng))
        )
    { }
};


namespace check_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
        {
            typedef check_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace check_range_detail


PSTADE_EGG_FUNCTION(make_check_range, check_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(checked, check_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
