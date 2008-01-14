#ifndef PSTADE_OVEN_UTF8_DECODED_HPP
#define PSTADE_OVEN_UTF8_DECODED_HPP
#include "./detail/prefix.hpp"


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
#include "./concepts.hpp"
#include "./detail/little_to_adaptor.hpp"
#include "./detail/u8_to_u32_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_decoded_detail {


    template< class U32Type >
    struct little
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


} // namespace utf8_decoded_detail


template< class U32Type = boost::uint32_t >
struct X_make_utf8_decoded :
    egg::function< utf8_decoded_detail::little<U32Type> >
{ };


PSTADE_OVEN_LITTLE_TO_ADAPTOR(utf8_decoded, (X_make_utf8_decoded<>::little_type))


} } // namespace pstade::oven


#endif
