#ifndef PSTADE_REMOVE_RCV_HPP
#define PSTADE_REMOVE_RCV_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade {


template< class T >
struct remove_rcv :
	boost::remove_reference<
		typename boost::remove_cv<T>::type
	>
{ };


} // namespace pstade


#endif
