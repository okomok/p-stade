#ifndef PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint8_t
#include <boost/regex/pending/unicode_iterator.hpp> // u32_to_u8_iterator
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_encode_range_detail {


    template<
        class Range,
        class U8T
    >
    struct super_ :
        iter_range<
            boost::u32_to_u8_iterator<
                typename range_iterator<Range>::type,
                U8T
            >
        >
    { };


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
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename utf8_encode_range_detail::super_<Range, U8T>::type super_t;

public:
    explicit utf8_encode_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_utf8_encode_range :
    callable<op_make_utf8_encode_range>
{
    template< class Myself, class Range, class U8T = boost::uint8_t >
    struct apply
    {
        typedef typename pass_by_value<U8T>::type u8_t;
        typedef utf8_encode_range<Range, u8_t> const type;
    };

    template< class Result, class Range, class U8T >
    Result call(Range& rng, U8T) const
    {
        return Result(rng);
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_utf8_encode_range, op_make_utf8_encode_range)
PSTADE_PIPABLE(utf8_encoded, op_make_utf8_encode_range)


} } // namespace pstade::oven


#endif
