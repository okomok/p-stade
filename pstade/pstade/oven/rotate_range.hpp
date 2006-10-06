#ifndef PSTADE_OVEN_ROTATE_RANGE_HPP
#define PSTADE_OVEN_ROTATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./joint_range.hpp"
#include "./range_base.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


namespace rotate_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef typename sub_range_base<ForwardRange>::type const rng_t;
        typedef joint_range<rng_t, rng_t> type;
    };


    template< class Super, class ForwardRange, class MiddleFun >
    Super make(ForwardRange& rng, MiddleFun fun)
    {
        typedef typename range_base<Super>::type base_t;
        typedef typename range_iterator<ForwardRange>::type iter_t;
        iter_t middle = fun(rng);
        return Super(base_t(middle, boost::end(rng)), base_t(boost::begin(rng), middle));
    }


} // namespace rotate_range_detail



template< class ForwardRange >
struct rotate_range :
    rotate_range_detail::super_<ForwardRange>::type,
    private as_lightweight_proxy< rotate_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeRangeConcept);
    typedef typename rotate_range_detail::super_<ForwardRange>::type super_t;

public:
    template< class MiddleFun >
    rotate_range(ForwardRange& rng, MiddleFun fun) :
        super_t(rotate_range_detail::make<super_t>(rng, fun))
    { }
};


namespace rotate_range_detail {


    struct baby_make
    {
        template< class Myself, class ForwardRange, class MiddleFun >
        struct apply
        {
            typedef rotate_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class MiddleFun >
        Result call(ForwardRange& rng, MiddleFun& fun)
        {
            return Result(rng, fun);
        }
    };


} // namespace rotate_range_detail


PSTADE_EGG_FUNCTION(make_rotate_range, rotate_range_detail::baby_make)
PSTADE_EGG_PIPABLE(rotated, rotate_range_detail::baby_make)


} } // namespace pstade::oven


#endif
