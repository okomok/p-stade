#ifndef PSTADE_REMOVE_CVR_HPP
#define PSTADE_REMOVE_CVR_HPP


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
struct remove_cvr :
    boost::remove_cv<
        typename boost::remove_reference<T>::type
    >
{ };


} // namespace pstade


#endif
