#ifndef PSTADE_GRAVY_TSSTREAM_HPP
#define PSTADE_GRAVY_TSSTREAM_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream>
#include "./sdk/tchar.hpp"


namespace pstade { namespace gravy {


    typedef
        std::basic_istringstream<TCHAR>
    itstringstream;

    typedef
        std::basic_ostringstream<TCHAR>
    otstringstream;

    typedef
        std::basic_stringstream<TCHAR>
    tstringstream;


} } // namespace pstade::gravy


#endif
