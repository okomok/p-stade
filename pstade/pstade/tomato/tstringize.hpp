#ifndef PSTADE_TOMATO_TSTRINGIZE_HPP
#define PSTADE_TOMATO_TSTRINGIZE_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/preprocessor/wstringize.hpp>


#include <boost/microsoft/sdk/tchar.hpp>


#define PSTADE_TOMATO_TSTRINGIZE(Text) PSTADE_TOMATO_TSTRINGIZE_I(Text)

	#define PSTADE_TOMATO_TSTRINGIZE_I(Text) PSTADE_TOMATO_TSTRINGIZE_II(#Text)
	#define PSTADE_TOMATO_TSTRINGIZE_II(Str) _T(Str)


#endif
