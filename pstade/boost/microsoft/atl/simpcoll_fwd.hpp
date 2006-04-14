#ifndef BOOST_MICROSOFT_ATL_SIMPCOLL_FWD_HPP
#define BOOST_MICROSOFT_ATL_SIMPCOLL_FWD_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_CSIMPLEARRAY


namespace ATL {


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY)

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
