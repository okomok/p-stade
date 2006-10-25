#ifndef PSTADE_OVEN_MB_ENCODE_RANGE_HPP
#define PSTADE_OVEN_MB_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/iterators/mb_from_wchar.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace mb_encode_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::archive::iterators::mb_from_wchar<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace mb_encode_range_detail


template< class Range >
struct mb_encode_range :
    mb_encode_range_detail::super_<Range>::type,
    private as_lightweight_proxy< mb_encode_range<Range> >
{
private:
    typedef typename mb_encode_range_detail::super_<Range>::type super_t;

public:
    explicit mb_encode_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace mb_encode_range_detail {


    struct baby_make
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef mb_encode_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace mb_encode_range_detail


PSTADE_EGG_FUNCTION(make_mb_encode_range, mb_encode_range_detail::baby_make)
PSTADE_EGG_PIPABLE(mb_encoded, mb_encode_range_detail::baby_make)


} } // namespace pstade::oven


#endif
