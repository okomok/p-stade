#ifndef PSTADE_OVEN_MB_ENCODE_RANGE_HPP
#define PSTADE_OVEN_MB_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/iterators/mb_from_wchar.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace mb_encode_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            boost::archive::iterators::mb_from_wchar<
                typename boost::range_result_iterator<Range>::type
            >
        > type;
    };


} // namespace mb_encode_range_detail


template< class Range >
struct mb_encode_range :
    mb_encode_range_detail::super_<Range>::type
{
private:
    typedef typename mb_encode_range_detail::super_<Range>::type super_t;

public:
    explicit mb_encode_range(Range& rng) :
        super_t(rng)
    { }
};


namespace mb_encode_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
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


PSTADE_EGG_FUNCTION(make_mb_encode_range, mb_encode_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(mb_encoded, mb_encode_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::mb_encode_range, 1)


#endif
