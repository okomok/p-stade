#ifndef PSTADE_TOMATO_RGB_HPP
#define PSTADE_TOMATO_RGB_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iomanip> // hex
#include <locale>
#include <sstream> // istringstream
#include <boost/cstdint.hpp> // uint32_t
#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/drop_range.hpp>


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


// What:
// Converts something like '#11AAFF' to 'COLORREF'.
// A 'wchar_t' is casted to 'char'. Take care.
//
template< class CharRange >
boost::optional<COLORREF> const
rgb(CharRange const& rng)
{
    if (boost::empty(rng))
        return boost::none;

    // See:
    // http://groups.google.com/group/comp.lang.c++.moderated/msg/3a2bbe7be45a9d80
    // http://d.hatena.ne.jp/y-hamigaki/20061017

    std::string tmp = rng|oven::dropped(1)|oven::copied;
    std::istringstream is(tmp);
    is.imbue(std::locale::classic());

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
