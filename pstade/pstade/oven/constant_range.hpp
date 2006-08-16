#ifndef PSTADE_OVEN_CONSTANT_RANGE_HPP
#define PSTADE_OVEN_CONSTANT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/param.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace constant_range_detail {


    template< class Range >
    struct constantify_fun
    {
        typedef typename range_reference<Range>::type ref_t;
        typedef typename range_value<Range>::type val_t;

        typedef typename affect_cvr<
            ref_t,
            typename boost::add_const<val_t>::type
        >::type result_type;

        result_type operator()(typename param<ref_t>::type x) const
        {
            return x;
        }
    };


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            boost::transform_iterator<
                constantify_fun<Range>,
                typename range_iterator<Range>::type
            >
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
    typedef typename super_t::iterator iter_t;

public:
    explicit constant_range(Range& rng) :
        super_t(
            iter_t(boost::begin(rng), constant_range_detail::constantify_fun<Range>()),
            iter_t(boost::end(rng),   constant_range_detail::constantify_fun<Range>())
        )
    { }
};


namespace constant_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
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


PSTADE_EGG_FUNCTION(make_constant_range, constant_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(constants, constant_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
