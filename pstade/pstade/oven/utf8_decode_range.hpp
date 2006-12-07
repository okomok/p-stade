#ifndef PSTADE_OVEN_UTF8_DECODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint32_t
#include <boost/regex/pending/unicode_iterator.hpp> // u8_to_u32_iterator
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_decode_range_detail {


    template<
        class Range,
        class Ucs4T
    >
    struct super_ :
        iter_range<
            boost::u8_to_u32_iterator<
                typename range_iterator<Range>::type,
                Ucs4T
            >
        >
    { };


} // namespace utf8_decode_range_detail


template<
    class Range,
    class Ucs4T = boost::uint32_t
>
struct utf8_decode_range :
    utf8_decode_range_detail::super_<Range, Ucs4T>::type,
    private as_lightweight_proxy< utf8_decode_range<Range, Ucs4T> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename utf8_decode_range_detail::super_<Range, Ucs4T>::type super_t;

public:
    explicit utf8_decode_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace utf8_decode_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Ucs4T = boost::uint32_t >
        struct apply
        {
            typedef typename pass_by_value<Ucs4T>::type ucs4_t;
            typedef utf8_decode_range<Range, ucs4_t> const type;
        };

        template< class Result, class Range, class Ucs4T >
        Result call(Range& rng, Ucs4T) const
        {
            return Result(rng);
        }

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return Result(rng);
        }
    };


} // namespace utf8_decode_range_detail


PSTADE_EGG_FUNCTION(make_utf8_decode_range, utf8_decode_range_detail::baby_make)
PSTADE_PIPABLE(utf8_decoded, op_make_utf8_decode_range)


} } // namespace pstade::oven


#endif
