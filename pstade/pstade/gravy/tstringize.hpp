#ifndef PSTADE_GRAVY_TSTRINGIZE_HPP
#define PSTADE_GRAVY_TSTRINGIZE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./sdk/tchar.hpp"


#define PSTADE_GRAVY_TSTRINGIZE(Text) PSTADE_GRAVY_TSTRINGIZE_I(Text)

    #define PSTADE_GRAVY_TSTRINGIZE_I(Text) PSTADE_GRAVY_TSTRINGIZE_II(#Text)
    #define PSTADE_GRAVY_TSTRINGIZE_II(Str) _T(Str)


#endif
