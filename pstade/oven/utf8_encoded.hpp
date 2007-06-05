#ifndef PSTADE_OVEN_UTF8_ENCODED_HPP
#define PSTADE_OVEN_UTF8_ENCODED_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */


#include <boost/cstdint.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/u32_to_u8_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class U8Type = boost::uint8_t >
struct op_make_utf8_encoded :
    callable< op_make_utf8_encoded<U8Type> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            detail::u32_to_u8_iterator<
                typename range_iterator<Range>::type,
                U8Type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_utf8_encoded, (op_make_utf8_encoded<>))
PSTADE_PIPABLE(utf8_encoded, (op_make_utf8_encoded<>))


} } // namespace pstade::oven


#endif
