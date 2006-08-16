#ifndef PSTADE_OVEN_UNIQUE_RANGE_HPP
#define PSTADE_OVEN_UNIQUE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./adjacent_filter_range.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./detail/equal_to.hpp"
#include "./detail/not.hpp"


namespace pstade { namespace oven {


namespace unique_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef adjacent_filter_range<
            ForwardRange,
            typename boost::result_of<detail::not_fun(detail::equal_to_fun)>::type
        > type;
    };


} // namespace unique_range_detail


template< class ForwardRange >
struct unique_range :
    unique_range_detail::super_<ForwardRange>::type,
    private as_lightweight_proxy< unique_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename unique_range_detail::super_<ForwardRange>::type super_t;

public:
    explicit unique_range(ForwardRange& rng) :
        super_t(rng, detail::not_(detail::equal_to))
    { }
};


namespace unique_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange >
        struct result
        {
            typedef unique_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace unique_range_detail


PSTADE_EGG_FUNCTION(make_unique_range, unique_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(uniqued, unique_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
