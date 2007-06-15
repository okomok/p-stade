#ifndef PSTADE_GRAVY_TIOSTREAM_HPP
#define PSTADE_GRAVY_TIOSTREAM_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/ios_init.hpp>


namespace pstade { namespace gravy {


    namespace {

    #if !defined(_UNICODE)
        std::istream&  tcin  = std::cin;
        std::ostream&  tcout = std::cout;
        std::ostream&  tcerr = std::cerr;
        std::ostream&  tclog = std::clog;
    #else
        std::wistream& tcin  = std::wcin;
        std::wostream& tcout = std::wcout;
        std::wostream& tcerr = std::wcerr;
        std::wostream& tclog = std::wclog;
    #endif

    } // unnamed


} } // namespace pstade::gravy


#endif
