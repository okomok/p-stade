#ifndef PSTADE_RADISH_SAFE_BOOL_HPP
#define PSTADE_RADISH_SAFE_BOOL_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/nullptr.hpp>


namespace pstade { namespace radish {


namespace safe_bool_detail {


    // Prefer member data pointer for faster code.
    struct box
    {
        int true_;
    };


} // namespace safe_bool_detail


typedef int safe_bool_detail::box:: *
safe_bool;


inline
safe_bool make_safe_bool(bool b)
{
    return b ? &safe_bool_detail::box::true_ : PSTADE_NULLPTR;
}


} } // namespace pstade::radish


#endif
