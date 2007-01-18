#ifndef PSTADE_OVEN_UTF8_ENCODED_HPP
#define PSTADE_OVEN_UTF8_ENCODED_HPP


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
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template<
    class U8T = boost::uint8_t
>
struct op_make_utf8_encoded :
    callable< op_make_utf8_encoded<U8T> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            iter_range<
                boost::u32_to_u8_iterator<
                    typename range_iterator<Range>::type,
                    U8T
                >
            > const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
        // PSTADE_CONCEPT_ASSERT((Readable<Range>));
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_utf8_encoded, (op_make_utf8_encoded<>))
PSTADE_PIPABLE(utf8_encoded, (op_make_utf8_encoded<>))


} } // namespace pstade::oven


#endif
