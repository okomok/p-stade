#ifndef PSTADE_APPLE_IS_CONTAINER_HPP
#define PSTADE_APPLE_IS_CONTAINER_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_cvr.hpp>
#include "./is_associative_container.hpp"
#include "./is_sequence.hpp"


namespace pstade { namespace apple {


template< class T >
struct is_container_impl :
    boost::mpl::or_<
        is_sequence<T>,
        is_associative_container<T>
    >
{ };


template< class T >
struct is_container :
    is_container_impl<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
