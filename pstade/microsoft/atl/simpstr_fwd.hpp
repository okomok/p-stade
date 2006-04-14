#ifndef BOOST_MICROSOFT_ATL_SIMPSTR_FWD_HPP
#define BOOST_MICROSOFT_ATL_SIMPSTR_FWD_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_SIMPLE_STRING


namespace ATL {


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLESTRING)

    template< class BaseType, bool mfcdll >
    class CSimpleStringT;

#else

    template< class BaseType >
    class CSimpleStringT;

#endif


template< class BaseType, const int t_nSize >
class CStaticString;


} // namespace ATL


#endif
