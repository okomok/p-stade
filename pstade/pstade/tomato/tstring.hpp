#ifndef PSTADE_TOMATO_TSTRING_HPP
#define PSTADE_TOMATO_TSTRING_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream>  // basic_stringstream
#include <string>   // basic_string
#include <boost/microsoft/sdk/tchar.hpp>


namespace pstade { namespace tomato {


typedef std::basic_string<TCHAR>
tstring;


typedef std::basic_stringstream<TCHAR>
tstringstream;


} } // namespace pstade::tomato


#define PSTADE_TOMATO_TSTRINGIZE(Text) PSTADE_TOMATO_TSTRINGIZE_I(Text)

    #define PSTADE_TOMATO_TSTRINGIZE_I(Text) PSTADE_TOMATO_TSTRINGIZE_II(#Text)
    #define PSTADE_TOMATO_TSTRINGIZE_II(Str) _T(Str)


#endif
