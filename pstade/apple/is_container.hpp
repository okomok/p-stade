#ifndef PSTADE_APPLE_IS_CONTAINER_HPP
#define PSTADE_APPLE_IS_CONTAINER_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/enable_if.hpp>
#include "./is_associative_container.hpp"
#include "./is_sequence.hpp"


namespace pstade { namespace apple {


template< class T, class = enabler >
struct is_container_impl :
    boost::mpl::or_<
        is_sequence<T>,
        is_associative_container<T>
    >
{ };


template< class T >
struct is_container :
    is_container_impl<
        typename boost::remove_cv<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
