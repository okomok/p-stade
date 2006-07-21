#ifndef PSTADE_OVEN_UTF8_DECODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint32_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u8_to_u32_iterator
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"


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
    utf8_decode_range_detail::super_<BidiRange, Ucs4T>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename utf8_decode_range_detail::super_<BidiRange, Ucs4T>::type super_t;

public:
    explicit utf8_decode_range(BidiRange& rng) :
        super_t(rng)
    { }
};


namespace utf8_decode_range_detail {


    struct baby_generator
    {
        template< class Unused, class BidiRange, class Ucs4T = boost::uint32_t >
        struct result
        {
            typedef typename boost::remove_cv<Ucs4T>::type ucs4_t;
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


PSTADE_EGG_FUNCTION(make_utf8_decode_range, utf8_decode_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(utf8_decoded, utf8_decode_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::utf8_decode_range, 2)


#endif
