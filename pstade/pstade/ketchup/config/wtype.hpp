#ifndef PSTADE_KETCHUP_CONFIG_WTYPE_HPP
#define PSTADE_KETCHUP_CONFIG_WTYPE_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef _WTL_NO_WTYPES
    #define KETCHUP_wtype_ns WTL
    namespace WTL {
        class CSize;
        class CPoint;
    }
#else
    #define KETCHUP_wtype_ns // ATL
    class CSize;
    class CPoint;
#endif


#endif
