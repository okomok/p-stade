#ifndef PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint8_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u32_to_u8_iterator
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


namespace utf8_encode_range_detail {


    template< class BidiRange, class U8T >
    struct super_
    {
        typedef boost::iterator_range<
            boost::u32_to_u8_iterator<
                typename range_iterator<BidiRange>::type,
                U8T
            >
        > type;
    };


} // namespace utf8_encode_range_detail


template< class BidiRange, class U8T = boost::uint8_t >
struct utf8_encode_range :
    utf8_encode_range_detail::super_<BidiRange, U8T>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename utf8_encode_range_detail::super_<BidiRange, U8T>::type super_t;

public:
    explicit utf8_encode_range(BidiRange& rng) :
        super_t(rng)
    { }
};


namespace utf8_encode_range_detail {


    struct baby_generator
    {
        template< class Unused, class BidiRange, class U8T = boost::uint8_t >
        struct result
        {
            typedef typename boost::remove_cv<U8T>::type u8_t;
            typedef utf8_encode_range<BidiRange, u8_t> const type;
        };

        template< class Result, class BidiRange, class U8T >
        Result call(BidiRange& rng, U8T)
        {
            return Result(rng);
        }

        template< class Result, class BidiRange >
        Result call(BidiRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace utf8_encode_range_detail


PSTADE_EGG_FUNCTION(make_utf8_encode_range, utf8_encode_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(utf8_encoded, utf8_encode_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::utf8_encode_range, 2)


#endif
