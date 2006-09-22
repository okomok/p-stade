#ifndef PSTADE_OVEN_PREPEND_RANGE_HPP
#define PSTADE_OVEN_PREPEND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ref.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./joint_range.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


namespace prepend_range_detail {


    template< class Value >
    struct init
    {
        typedef boost::base_from_member< single_range<Value> > type;
    };


    template< class Range, class Value >
    struct super_
    {
        typedef joint_range< single_range<Value>, Range > type;
    };


} // namespace prepend_range_detail


template< class Range, class Value >
struct prepend_range :
    private prepend_range_detail::init<Value>::type,
    prepend_range_detail::super_<Range, Value>::type,
    private as_lightweight_proxy< prepend_range<Range, Value> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename prepend_range_detail::init<Value>::type init_t;
    typedef typename prepend_range_detail::super_<Range, Value>::type super_t;

public:
    prepend_range(Range& rng, Value& v) :
        init_t(boost::ref(v)),
        super_t(init_t::member, rng)
    { }
};


namespace prepend_range_detail {


    struct baby_make
    {
        template< class Unused, class Range, class Value >
        struct apply
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


PSTADE_EGG_FUNCTION(make_prepend_range, prepend_range_detail::baby_make)
PSTADE_EGG_PIPABLE(prepended, prepend_range_detail::baby_make)


} } // namespace pstade::oven


#endif
