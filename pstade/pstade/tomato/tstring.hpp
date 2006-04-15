#ifndef PSTADE_TOMATO_TSTRING_HPP
#define PSTADE_TOMATO_TSTRING_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <boost/microsoft/sdk/tchar.hpp>


namespace pstade { namespace tomato {


typedef std::basic_string<TCHAR>
tstring;


} } // namespace pstade::tomato


#endif
