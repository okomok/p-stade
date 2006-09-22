#ifndef PSTADE_OVEN_CONSTANT_RANGE_HPP
#define PSTADE_OVEN_CONSTANT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_const.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // identity
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./transform_range.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace constant_range_detail {


    template< class Range >
    struct reference
    {
        typedef typename range_reference<Range>::type ref_t;
        typedef typename range_value<Range>::type val_t;

        typedef typename affect_cvr<
            ref_t,
            typename boost::add_const<val_t>::type
        >::type type;
    };


    template< class Range >
    struct super_
    {
        typedef transform_range<
            Range,
            identity_fun,
            typename reference<Range>::type
        > type;
    };


} // namespace constant_range_detail


template< class Range >
struct constant_range :
    constant_range_detail::super_<Range>::type,
    private as_lightweight_proxy< constant_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename constant_range_detail::super_<Range>::type super_t;

public:
    explicit constant_range(Range& rng) :
        super_t(rng, identity)
    { }
};


namespace constant_range_detail {


    struct baby_make
    {
        template< class Unused, class Range >
        struct apply
        {
            typedef constant_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace constant_range_detail


PSTADE_EGG_FUNCTION(make_constant_range, constant_range_detail::baby_make)
PSTADE_EGG_PIPABLE(constants, constant_range_detail::baby_make)


} } // namespace pstade::oven


#endif
