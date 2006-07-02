#ifndef PSTADE_OVEN_SEQUENCE_CAST_HPP
#define PSTADE_OVEN_SEQUENCE_CAST_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Deprecated and renamed to 'constructor/construct'.


#include "./construct.hpp"


namespace pstade { namespace oven {


template< class T, class Range > inline
T sequence_cast(const Range& rng)
{
    return oven::constructor<T>(rng);
}


template< class Range > inline const
construct_detail::temp<Range> sequence(const Range& rng)
{
    return oven::construct(rng);
}


} } // namespace pstade::oven


#endif
