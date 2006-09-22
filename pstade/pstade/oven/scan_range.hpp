#ifndef PSTADE_OVEN_SCAN_RANGE_HPP
#define PSTADE_OVEN_SCAN_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // plus
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./scan_iterator.hpp"


namespace pstade { namespace oven {


namespace scan_range_detail {


    template< class Range, class State, class BinaryFun >
    struct super_
    {
        typedef boost::iterator_range<
            scan_iterator<
                typename range_iterator<Range>::type,
                State,
                BinaryFun
            >
        > type;
    };


} // namespace scan_range_detail


template< class Range, class State, class BinaryFun = plus_fun >
struct scan_range :
    scan_range_detail::super_<Range, State, BinaryFun>::type,
    private as_lightweight_proxy< scan_range<Range, State, BinaryFun> >
{
    typedef Range pstade_oven_range_base_type;
    typedef State state_type;
    typedef BinaryFun function_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename scan_range_detail::super_<Range, State, BinaryFun>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    scan_range(Range& rng, State const& init, BinaryFun const& fun = pstade::plus) :
        super_t(
            iter_t(boost::begin(rng), init, fun),
            iter_t(boost::end(rng),   init, fun)
        )
    { }
};


namespace scan_range_detail {


    struct baby_make
    {
        template< class Unused, class Range, class State, class BinaryFun = plus_fun >
        struct apply
        {
            typedef typename pass_by_value<BinaryFun>::type fun_t;
            typedef typename pass_by_value<State>::type sta_t;
            typedef scan_range<Range, sta_t, fun_t> const type;
        };

        template< class Result, class Range, class State, class BinaryFun >
        Result call(Range& rng, State const& init, BinaryFun& fun)
        {
            return Result(rng, init, fun);
        }

        template< class Result, class Range, class State >
        Result call(Range& rng, State const& init)
        {
            return Result(rng, init);
        }
    };


} // namespace scan_range_detail


PSTADE_EGG_FUNCTION(make_scan_range, scan_range_detail::baby_make)
PSTADE_EGG_PIPABLE(scanned, scan_range_detail::baby_make)


} } // namespace pstade::oven


#endif
