#ifndef PSTADE_TOMATO_GARLIC_CUSTOMIZATION_HPP
#define PSTADE_TOMATO_GARLIC_CUSTOMIZATION_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/coll_fwd.hpp> // CAtlArray/List
#include <pstade/apple/atl/config.hpp> // TEMPLATE_PARAMS/ARGS
#include <pstade/apple/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/overload.hpp>


// strings
//

template< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
void pstade_garlic_push_back(
    ATL::CSimpleStringT< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str,
    TCHAR ch, pstade::overload<>)
{
    str.AppendChar(ch);
}


inline
void pstade_garlic_push_back(WTL::CString& str,
    TCHAR ch, pstade::overload<>)
{
    str += ch;
}


// collections
//

template< class E, class ETraits, class Value > inline
void pstade_garlic_push_back(
    ATL::CAtlArray<E, ETraits>& arr,
    Value const& val, pstade::overload<>)
{
    arr.Add(val);
}


template< class E, class ETraits, class Value > inline
void pstade_garlic_push_back(
    ATL::CAtlList<E, ETraits>& lst,
    Value const& val, pstade::overload<>)
{
    lst.AddTail(val);
}


template< PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS, class Value > inline
void pstade_garlic_push_back(
    ATL::CSimpleArray< PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr,
    Value const& val, pstade::overload<>)
{
#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLEARRAY)
    arr.Add(val);
#else
    Value val_(val);
    arr.Add(val_);
#endif
}


#endif
