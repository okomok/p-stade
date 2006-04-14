#ifndef PSTADE_IF_DEBUG_HPP
#define PSTADE_IF_DEBUG_HPP


// PStade.Wine
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(NDEBUG) || defined(PSTADE_IF_DEBUG_DEBUG)

	#define PSTADE_IF_DEBUG(X) \
		X \
	/**/

#else

	#define PSTADE_IF_DEBUG(X) \
	/**/

#endif


#endif
