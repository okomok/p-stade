#ifndef PSTADE_APPLE_IS_SEQUENCE_HPP
#define PSTADE_APPLE_IS_SEQUENCE_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <pstade/remove_rcv.hpp>
#include "./is_vector.hpp"
#include "./is_deque.hpp"
#include "./is_list.hpp"
#include "./is_basic_string.hpp"


namespace pstade { namespace apple {


template< class T >
struct is_sequence_impl :
    boost::mpl::or_<
        is_vector<T>,
        is_deque<T>,
        is_list<T>,
        is_basic_string<T>
    >
{ };


template< class T >
struct is_sequence :
    is_sequence_impl< typename remove_rcv<T>::type >
{ };


} } // namespace pstade::apple


#endif
