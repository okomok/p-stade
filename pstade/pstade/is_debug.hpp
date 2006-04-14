#ifndef PSTADE_IS_DEBUG_HPP
#define PSTADE_IS_DEBUG_HPP


// PStade.Wine
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace pstade {


template< class = void >
struct is_debug :
#if !defined(NDEBUG)
	boost::mpl::true_ 
#else
	boost::mpl::false_
#endif
{ };


} // namespace pstade


#endif
