#ifndef PSTADE_TOMATO_TSTREAM_HPP
#define PSTADE_TOMATO_TSTREAM_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>


#if !defined(_UNICODE)
    #define PSTADE_TOMATO_TCIN  std::cin
    #define PSTADE_TOMATO_TCOUT std::cout
    #define PSTADE_TOMATO_TCERR std::cerr
    #define PSTADE_TOMATO_TCLOG std::clog
#else
    #define PSTADE_TOMATO_TCIN  std::wcin
    #define PSTADE_TOMATO_TCOUT std::wcout
    #define PSTADE_TOMATO_TCERR std::wcerr
    #define PSTADE_TOMATO_TCLOG std::wclog
#endif


#endif
