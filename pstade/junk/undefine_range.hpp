#ifndef PSTADE_OVEN_UNDEFINE_RANGE_HPP
#define PSTADE_OVEN_UNDEFINE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./undefine_iterator.hpp"


namespace pstade { namespace oven {


namespace undefine_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            undefine_iterator<
                typename range_iterator<Range>::type
            >
        > type;
    };


} // namespace undefine_range_detail


template< class Range >
struct undefine_range :
    undefine_range_detail::super_<Range>::type,
    private lightweight_proxy< undefine_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename undefine_range_detail::super_<Range>::type super_t;

public:
    explicit undefine_range(Range& rng) :
        super_t(rng)
    { }
};


namespace undefine_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
        {
            typedef undefine_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace undefine_range_detail


PSTADE_EGG_FUNCTION(make_undefine_range, undefine_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(undefined, undefine_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
