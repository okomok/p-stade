#ifndef PSTADE_OVEN_PREPEND_RANGE_HPP
#define PSTADE_OVEN_PREPEND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ref.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./joint_range.hpp"
#include "./range_adaptor.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


template< class Range, class Value >
struct prepend_range :
    private boost::base_from_member< single_range<Value> >,
    joint_range< single_range<Value>, Range >
{
private:
    typedef boost::base_from_member< single_range<Value> > single_range_bt;
    typedef joint_range< single_range<Value>, Range > super_t;

public:
    prepend_range(Range& rng, Value& v) :
        single_range_bt(boost::ref(v)),
        super_t(single_range_bt::member, rng)
    { }
};


namespace prepend_range_detail {


    struct baby_generator
    {
        template< class Range, class Value >
        struct result
        {
            typedef prepend_range<Range, Value> const type;
        };

        template< class Result, class Range, class Value >
        Result call(Range& rng, Value& v)
        {
            return Result(rng, v);
        }
    };


} // namespace prepend_range_detail


PSTADE_EGG_FUNCTION(make_prepend_range, prepend_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(prepended, prepend_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::prepend_range, 2)


#endif
