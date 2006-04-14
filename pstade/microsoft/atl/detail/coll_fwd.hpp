#ifndef BOOST_MICROSOFT_ATL_DETAIL_COLL_FWD_HPP
#define BOOST_MICROSOFT_ATL_DETAIL_COLL_FWD_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_SIMPLE_ARRAY
#include <guiddef.h> // IID


namespace ATL {


template< class E, class ETraits >
class CAtlArray;

template< class E >
class CAutoPtrArray;

template< class I, const IID *piid >
class CInterfaceArray;


template< class E, class ETraits >
class CAtlList;

template< class E >
class CAutoPtrList;

template< class I, const IID *piid >
class CInterfaceList;


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_SIMPLE_ARRAY)

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
