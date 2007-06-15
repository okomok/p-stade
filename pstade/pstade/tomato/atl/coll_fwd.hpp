#ifndef PSTADE_TOMATO_ATL_COLL_FWD_HPP
#define PSTADE_TOMATO_ATL_COLL_FWD_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "../sdk/basetyps.hpp" // IID


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

template< class E, class Allocator >
class CHeapPtrList;

template< class I, const IID *piid >
class CInterfaceList;


template< class K, class V, class KTraits, class VTraits >
class CAtlMap;

template< class K, class V, class KTraits, class VTraits >
class CRBTree;

template< class K, class V, class KTraits, class VTraits >
class CRBMap;

template< class K, class V, class KTraits, class VTraits >
class CRBMultiMap;


} // namespace ATL


#endif
