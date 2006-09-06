#ifndef PSTADE_TOMATO_TSTREAM_HPP
#define PSTADE_TOMATO_TSTREAM_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/ios_init.hpp>


namespace pstade { namespace tomato {

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

} } // namespace pstade::tomato

#endif
