#ifndef PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint8_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u32_to_u8_iterator
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_encode_range_detail {


    template<
        class Range,
        class U8T
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::u32_to_u8_iterator<
                typename range_iterator<Range>::type,
                U8T
            >
        > type;
    };


} // namespace utf8_encode_range_detail


template<
    class Range,
    class U8T = boost::uint8_t
>
struct utf8_encode_range :
    utf8_encode_range_detail::super_<Range, U8T>::type,
    private as_lightweight_proxy< utf8_encode_range<Range, U8T> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename utf8_encode_range_detail::super_<Range, U8T>::type super_t;

public:
    explicit utf8_encode_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace utf8_encode_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class U8T = boost::uint8_t >
        struct apply
        {
            typedef typename pass_by_value<U8T>::type u8_t;
            typedef utf8_encode_range<Range, u8_t> const type;
        };

        template< class Result, class Range, class U8T >
        Result call(Range& rng, U8T)
        {
            return Result(rng);
        }

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace utf8_encode_range_detail


PSTADE_EGG_FUNCTION(make_utf8_encode_range, utf8_encode_range_detail::baby_make)
PSTADE_EGG_PIPABLE(utf8_encoded, utf8_encode_range_detail::baby_make)


} } // namespace pstade::oven


#endif
