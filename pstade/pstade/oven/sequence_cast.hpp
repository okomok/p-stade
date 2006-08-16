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
// Deprecated.


#include "./copy_range.hpp"


namespace pstade { namespace oven {


template< class T, class Range > inline
T sequence_cast(Range const& rng)
{
    return oven::copy_range<T>(rng);
}


template< class Range > inline
copy_range_detail::temp<Range const> const sequence(Range const& rng)
{
    return rng|copied;
}


} } // namespace pstade::oven


#endif
