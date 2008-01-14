#ifndef PSTADE_APPLE_HAS_RANGE_CONSTRUCTOR_HPP
#define PSTADE_APPLE_HAS_RANGE_CONSTRUCTOR_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// SGI documentation is outdated.


#include <boost/mpl/or.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/plain.hpp>
#include "./is_associative_container.hpp"
#include "./is_sequence.hpp"


namespace pstade { namespace apple {


template< class T, class = enabler >
struct has_range_constructor_impl :
    boost::mpl::or_<
        is_sequence<T>,
        is_associative_container<T>
    >
{ };


template< class T >
struct has_range_constructor :
    has_range_constructor_impl<
        typename plain<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
