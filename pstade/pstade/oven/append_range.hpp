#ifndef PSTADE_OVEN_APPEND_RANGE_HPP
#define PSTADE_OVEN_APPEND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ref.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./joint_range.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


template< class Range, class Value >
struct append_range :
    private boost::base_from_member< single_range<Value> >,
    joint_range< Range, single_range<Value> >,
    private lightweight_proxy< append_range<Range, Value> >
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef boost::base_from_member< single_range<Value> > single_range_bt;
    typedef joint_range< Range, single_range<Value> > super_t;

public:
    append_range(Range& rng, Value& v) :
        single_range_bt(boost::ref(v)),
        super_t(rng, single_range_bt::member)
    { }
};


namespace append_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class Value >
        struct result
        {
            typedef append_range<Range, Value> const type;
        };

        template< class Result, class Range, class Value >
        Result call(Range& rng, Value& v)
        {
            return Result(rng, v);
        }
    };


} // namespace append_range_detail


PSTADE_EGG_FUNCTION(make_append_range, append_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(appended, append_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
