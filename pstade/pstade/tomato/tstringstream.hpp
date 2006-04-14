#ifndef PSTADE_TOMATO_TSTRINGSTREAM_HPP
#define PSTADE_TOMATO_TSTRINGSTREAM_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream> // basic_stringstream
#include <boost/microsoft/sdk/tchar.hpp>


namespace pstade { namespace tomato {


typedef std::basic_stringstream<TCHAR>
tstringstream;


} } // namespace pstade::tomato


#endif
