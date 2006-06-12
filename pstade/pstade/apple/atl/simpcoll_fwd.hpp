#ifndef PSTADE_APPLE_ATL_SIMPCOLL_FWD_HPP
#define PSTADE_APPLE_ATL_SIMPCOLL_FWD_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp" // ATL_HAS_OLD_CSIMPLEARRAY


namespace ATL {


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLEARRAY)

    template< class T, class TEqual >
    class CSimpleArray;

#else

    template< class T >
    class CSimpleArray;

    template< class T >
    class CSimpleValArray;

#endif


} // namespace ATL


#endif
