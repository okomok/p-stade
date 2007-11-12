#ifndef PSTADE_OVEN_UTF16_ENCODED_HPP
#define PSTADE_OVEN_UTF16_ENCODED_HPP
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
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/u32_to_u16_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf16_encoded_detail {


    template< class U16Type >
    struct baby
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef
                detail::u32_to_u16_iterator<
                    typename range_iterator<Range>::type,
                    U16Type
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


} // utf16_encoded_detail


template< class U16Type = boost::uint16_t >
struct X_make_utf16_encoded :
    egg::function< utf16_encoded_detail::baby<U16Type> >
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(utf16_encoded, (X_make_utf16_encoded<>::baby_type))


} } // namespace pstade::oven


#endif
