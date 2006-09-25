#ifndef PSTADE_APPLE_ATL_SIMPCOLL_FWD_HPP
#define PSTADE_APPLE_ATL_SIMPCOLL_FWD_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp" // APPLE_ATL_HAS_OLD_CSIMPLECOLL


namespace ATL {


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)

    template< class T, class TEqual >
    class CSimpleArray;

    template< class TKey, class TVal, class TEqual >
    class CSimpleMap;

#else

    template< class T >
    class CSimpleArray;

    template< class T >
    class CSimpleValArray;

    template< class TKey, class TVal >
    class CSimpleMap;

#endif


} // namespace ATL


#endif
