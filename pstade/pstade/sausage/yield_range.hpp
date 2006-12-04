#ifndef PSTADE_SAUSAGE_YIELD_RANGE_HPP
#define PSTADE_SAUSAGE_YIELD_RANGE_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/oven/as_lightweight_proxy.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./yield_iterator.hpp"


namespace pstade { namespace sausage {


namespace yield_range_detail {


    template< class Routine >
    struct super_ :
        oven::iter_range<
            yield_iterator<Routine>
        >
    { };


} // namespace yield_range_detail


template< class Routine >
struct yield_range :
    yield_range_detail::super_<Routine>::type,
    private oven::as_lightweight_proxy< yield_range<Routine> >
{
private:
    typedef typename yield_range_detail::super_<Routine>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit yield_range(Routine const& rou) :
        super_t(iter_t(rou), iter_t())
    { }
};


namespace yield_range_detail {


    struct baby_make
    {
        template< class Myself, class Routine >
        struct apply
        {
            typedef typename pass_by_value<Routine>::type rou_t;
            typedef yield_range<rou_t> const type;
        };

        template< class Result, class Routine >
        Result call(Routine& rou) const
        {
            return Result(rou);
        }
    };


} // namespace yield_range_detail


PSTADE_EGG_FUNCTION(make_yield_range, yield_range_detail::baby_make)
PSTADE_PIPABLE(yielded, make_yield_range_fun)


} } // namespace pstade::sausage


#endif
