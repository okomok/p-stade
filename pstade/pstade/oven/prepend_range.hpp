#ifndef PSTADE_OVEN_PREPEND_RANGE_HPP
#define PSTADE_OVEN_PREPEND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/base_from.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unparenthesize.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./joint_range.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


namespace prepend_range_detail {


    template< class Value >
    struct init_single :
        base_from< single_range<Value> >
    { };


    template< class Range, class Value >
    struct super_
    {
        typedef joint_range< single_range<Value>, Range > type;
    };


} // namespace prepend_range_detail


template< class Range, class Value >
struct prepend_range :
    private prepend_range_detail::init_single<Value>::type,
    prepend_range_detail::super_<Range, Value>::type,
    private as_lightweight_proxy< prepend_range<Range, Value> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef prepend_range type;

private:
    typedef typename prepend_range_detail::init_single<Value>::type init_t;
    typedef typename init_t::member_type single_t;
    typedef typename prepend_range_detail::super_<Range, Value>::type super_t;

public:
    prepend_range(Range& rng, Value& v) :
        init_t(single_t(v)),
        super_t(init_t::member, rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_prepend_range,
    PSTADE_UNPARENTHESIZE((prepend_range< deduce_to_qualified<from_1>, deduce_to_qualified<from_2> >)) const)
PSTADE_PIPABLE(prepended, op_make_prepend_range)


} } // namespace pstade::oven


#endif
