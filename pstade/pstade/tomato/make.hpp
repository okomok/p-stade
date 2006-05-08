#ifndef PSTADE_TOMATO_MAKE_HPP
#define PSTADE_TOMATO_MAKE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>


namespace pstade { namespace tomato {


template < class WordT > inline
DWORD make_long(WordT wLow, WordT wHigh)
{
    return MAKELONG(wLow, wHigh);
}


inline
TCHAR *make_intresource(WORD wInteger)
{
    return MAKEINTRESOURCE(wInteger);
}


} } // namespace pstade::tomato


#endif
