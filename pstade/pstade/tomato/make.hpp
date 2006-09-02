#ifndef PSTADE_TOMATO_MAKE_HPP
#define PSTADE_TOMATO_MAKE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>


namespace pstade { namespace tomato {


template< class Word1, class Word2 > inline
DWORD make_LONG(Word1 wLow, Word2 wHigh)
{
    return MAKELONG(wLow, wHigh);
}


template< class Word > inline
TCHAR *make_INTRESOURCE(Word wInteger)
{
    return MAKEINTRESOURCE(wInteger);
}


template< class Word1, class Word2 > inline
WPARAM make_WPARAM(Word1 wLow, Word2 wHigh)
{
    return MAKEWPARAM(wLow, wHigh);
}


template< class Word1, class Word2 > inline
LPARAM make_LPARAM(Word1 wLow, Word2 wHigh)
{
    return MAKELPARAM(wLow, wHigh);
}


template< class Word1, class Word2 > inline
LRESULT make_LRESULT(Word1 wLow, Word2 wHigh)
{
    return MAKELRESULT(wLow, wHigh);
}


} } // namespace pstade::tomato


#endif
