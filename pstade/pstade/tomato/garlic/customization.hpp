#ifndef PSTADE_TOMATO_GARLIC_CUSTOMIZATION_HPP
#define PSTADE_TOMATO_GARLIC_CUSTOMIZATION_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/coll_fwd.hpp> // CAtlArray/List
#include <boost/microsoft/atl/config.hpp> // TEMPLATE_PARAMS/ARGS
#include <boost/microsoft/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <boost/microsoft/wtl/misc.hpp> // CString
#include <pstade/overload.hpp>


// strings
//

template< BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
void pstade_garlic_push_back(
	ATL::CSimpleStringT< BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str,
	TCHAR ch, pstade::overload)
{
	str.AppendChar(ch);
}


void pstade_garlic_push_back(WTL::CString& str,
	TCHAR ch, pstade::overload)
{
	str += ch;
}


// collections
//

template< class E, class ETraits, class ValueT >
void pstade_garlic_push_back(
	ATL::CAtlArray<E, ETraits>& arr,
	const ValueT& val, pstade::overload)
{
	arr.Add(val);
}


template< class E, class ETraits, class ValueT >
void pstade_garlic_push_back(
	ATL::CAtlList<E, ETraits>& lst,
	const ValueT& val, pstade::overload)
{
	lst.AddTail(val);
}


template< BOOST_MICROSOFT_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS, class ValueT >
void pstade_garlic_push_back(
	ATL::CSimpleArray< BOOST_MICROSOFT_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr,
	const ValueT& val, pstade::overload)
{
#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY)
	arr.Add(val);
#else
	ValueT val_(val);
	arr.Add(val_);
#endif
}


#endif
