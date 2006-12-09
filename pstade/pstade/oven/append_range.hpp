#ifndef PSTADE_OVEN_APPEND_RANGE_HPP
#define PSTADE_OVEN_APPEND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/base_from.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./joint_range.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


namespace append_range_detail {


    template< class Value >
    struct init_single :
        base_from< single_range<Value> >
    { };


    template< class Range, class Value >
    struct super_
    {
        typedef joint_range< Range, single_range<Value> > type;
    };


} // namespace append_range_detail


template< class Range, class Value >
struct append_range :
    private append_range_detail::init_single<Value>::type,
    append_range_detail::super_<Range, Value>::type,
    private as_lightweight_proxy< append_range<Range, Value> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename append_range_detail::init_single<Value>::type init_t;
    typedef typename init_t::member_type single_t;
    typedef typename append_range_detail::super_<Range, Value>::type super_t;

public:
    append_range(Range& rng, Value& v) :
        init_t(single_t(v)),
        super_t(rng, init_t::member)
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_append_range :
    callable<op_make_append_range>
{
    template< class Myself, class Range, class Value >
    struct apply
    {
        typedef append_range<Range, Value> const type;
    };

    template< class Result, class Range, class Value >
    Result call(Range& rng, Value& v) const
    {
        return Result(rng, v);
    }
};


PSTADE_CONSTANT(make_append_range, op_make_append_range)
PSTADE_PIPABLE(appended, op_make_append_range)


} } // namespace pstade::oven


#endif
