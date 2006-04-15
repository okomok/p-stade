#ifndef BOOST_MICROSOFT_ATL_COLL_FWD_HPP
#define BOOST_MICROSOFT_ATL_COLL_FWD_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/guiddef.hpp> // IID


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


} // namespace ATL


#endif
