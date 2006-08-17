#ifndef PSTADE_TOMATO_RGB_HPP
#define PSTADE_TOMATO_RGB_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iomanip> // hex
#include <sstream> // istringstream
#include <boost/cstdint.hpp> // uint32_t
#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/slice_range.hpp>


namespace pstade { namespace tomato {


template < class ByteT > inline
COLORREF rgb(ByteT byRed, ByteT byGreen, ByteT byBlue)
{
    return RGB(byRed, byGreen, byBlue);
}


inline
BYTE get_r_value(DWORD rgb)
{
    return GetRValue(rgb);
}


inline
BYTE get_g_value(DWORD rgb)
{
    return GetGValue(rgb);
}


inline
BYTE get_b_value(DWORD rgb)
{
    return GetBValue(rgb);
}


template< class Range >
boost::optional<COLORREF> const
rgb(Range const& rng)
{
    if (boost::empty(rng))
        return boost::none;

    // See:
    // http://groups.google.com/group/comp.lang.c++.moderated/msg/3a2bbe7be45a9d80
    //
    std::string tmp = rng|oven::sliced(1, 0)|oven::copied;
    std::istringstream is(tmp);

    boost::uint32_t n;
    if (!(is >> std::hex >> n))
        return boost::none;

    boost::uint32_t r = (n & 0xFF0000) >> 16;
    boost::uint32_t g = (n & 0xFF00) >> 8;
    boost::uint32_t b = (n & 0xFF);
    return boost::optional<COLORREF>(tomato::rgb(r, g, b));
}


} } // namespace pstade::tomato


#endif
