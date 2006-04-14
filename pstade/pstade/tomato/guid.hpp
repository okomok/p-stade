#ifndef PSTADE_TOMATO_GUID_HPP
#define PSTADE_TOMATO_GUID_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// But template arguments must be extern likage...


#include <boost/microsoft/sdk/guiddef.hpp> // IID
#include <boost/preprocessor/cat.hpp>


#define PSTADE_TOMATO_GUID(Name, L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8) \
	inline \
	const IID& BOOST_PP_CAT(pstade_tomato_guid_of_, Name)() \
	{ \
		static const IID iid = { \
			L, W1, W2, { B1, B2, B3, B4, B5, B6, B7, B8 } \
		}; \
		return iid; \
	} \
	namespace { \
		static const IID& Name = BOOST_PP_CAT(pstade_tomato_guid_of_, Name); \
	} \
/**/


#endif
