#ifndef PSTADE_RADISH_DETAIL_SAFE_BOOL_HPP
#define PSTADE_RADISH_DETAIL_SAFE_BOOL_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'safe_bool'
//
// at <boost/spirit/core/safe_bool.hpp>


#include <pstade/nullptr.hpp>


namespace pstade { namespace radish { namespace detail {


// Prefer member data pointer for faster code.
struct safe_bool_box { int true_; };


typedef int safe_bool_box:: *
safe_bool;


// Not objects but functions for faster code.
// VC7.1 generates a simple code as expected.
//
inline
safe_bool safe_true()
{
    return &safe_bool_box::true_;
}

inline
safe_bool safe_false()
{
    return PSTADE_NULLPTR;
}


} } } // namespace pstade::radish::detail


#endif
