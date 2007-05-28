#ifndef PSTADE_OVEN_UTF8_DECODED_HPP
#define PSTADE_OVEN_UTF8_DECODED_HPP


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


#include "./detail/prelude.hpp"
#include <boost/cstdint.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/u8_to_u32_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class U32Type = boost::uint32_t >
struct op_make_utf8_decoded :
    callable< op_make_utf8_decoded<U32Type> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            detail::u8_to_u32_iterator<
                typename range_iterator<Range>::type,
                U32Type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_utf8_decoded, (op_make_utf8_decoded<>))
PSTADE_PIPABLE(utf8_decoded, (op_make_utf8_decoded<>))


} } // namespace pstade::oven


#endif
