#ifndef PSTADE_OVEN_UTF8_DECODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint32_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u8_to_u32_iterator
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_decode_range_detail {


    template< class BidiRange, class Ucs4T >
    struct super_
    {
        typedef boost::iterator_range<
            boost::u8_to_u32_iterator<
                typename range_iterator<BidiRange>::type,
                Ucs4T
            >
        > type;
    };


} // namespace utf8_decode_range_detail


template< class BidiRange, class Ucs4T = boost::uint32_t >
struct utf8_decode_range :
    utf8_decode_range_detail::super_<BidiRange, Ucs4T>::type,
    private as_lightweight_proxy< utf8_decode_range<BidiRange, Ucs4T> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename utf8_decode_range_detail::super_<BidiRange, Ucs4T>::type super_t;

public:
    explicit utf8_decode_range(BidiRange& rng) :
        super_t(rng)
    { }
};


namespace utf8_decode_range_detail {


    struct baby_make
    {
        template< class Unused, class BidiRange, class Ucs4T = boost::uint32_t >
        struct result
        {
            typedef typename pass_by_value<Ucs4T>::type ucs4_t;
            typedef utf8_decode_range<BidiRange, ucs4_t> const type;
        };

        template< class Result, class BidiRange, class Ucs4T >
        Result call(BidiRange& rng, Ucs4T)
        {
            return Result(rng);
        }

        template< class Result, class BidiRange >
        Result call(BidiRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace utf8_decode_range_detail


PSTADE_EGG_FUNCTION(make_utf8_decode_range, utf8_decode_range_detail::baby_make)
PSTADE_EGG_PIPABLE(utf8_decoded, utf8_decode_range_detail::baby_make)


} } // namespace pstade::oven


#endif
