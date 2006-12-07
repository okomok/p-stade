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
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./joint_range.hpp"
#include "./range_base.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


namespace rotate_range_detail {


    template< class Range >
    struct super_
    {
        typedef typename sub_range_base<Range>::type const rng_t;
        typedef joint_range<rng_t, rng_t> type;
    };


    template< class Super, class Range, class MiddleFun >
    Super make(Range& rng, MiddleFun fun)
    {
        typedef typename range_base<Super>::type base_t;
        typedef typename range_iterator<Range>::type iter_t;
        iter_t middle = fun(rng);
        return Super(base_t(middle, boost::end(rng)), base_t(boost::begin(rng), middle));
    }


} // namespace rotate_range_detail



template< class Range >
struct rotate_range :
    rotate_range_detail::super_<Range>::type,
    private as_lightweight_proxy< rotate_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename rotate_range_detail::super_<Range>::type super_t;

public:
    template< class MiddleFun >
    rotate_range(Range& rng, MiddleFun fun) :
        super_t(rotate_range_detail::make<super_t>(rng, fun))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace rotate_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class MiddleFun >
        struct apply
        {
            typedef rotate_range<Range> const type;
        };

        template< class Result, class Range, class MiddleFun >
        Result call(Range& rng, MiddleFun& fun) const
        {
            return Result(rng, fun);
        }
    };


} // namespace rotate_range_detail


PSTADE_EGG_FUNCTION(make_rotate_range, rotate_range_detail::baby_make)
PSTADE_PIPABLE(rotated, op_make_rotate_range)


} } // namespace pstade::oven


#endif
