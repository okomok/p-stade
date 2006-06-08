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


template< class WordT > inline
DWORD make_LONG(WordT wLow, WordT wHigh)
{
    return MAKELONG(wLow, wHigh);
}


template< class WordT > inline
TCHAR *make_INTRESOURCE(WordT wInteger)
{
    return MAKEINTRESOURCE(wInteger);
}


template< class WordT > inline
WPARAM make_WPARAM(WordT wLow, WordT wHigh)
{
    return MAKEWPARAM(wLow, wHigh);
}


template< class WordT > inline
LPARAM make_LPARAM(WordT wLow, WordT wHigh)
{
    return MAKELPARAM(wLow, wHigh);
}


template< class WordT > inline
LRESULT make_LRESULT(WordT wLow, WordT wHigh)
{
    return MAKELRESULT(wLow, wHigh);
}


} } // namespace pstade::tomato


#endif
