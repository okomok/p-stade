#ifndef PSTADE_APPLE_IS_BOOST_RANGE_HPP
#define PSTADE_APPLE_IS_BOOST_RANGE_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_array.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/remove_rcv.hpp>
#include "./is_sequence.hpp"


namespace pstade { namespace apple {


namespace is_boost_range_detail {


    PSTADE_HAS_TYPE(iterator)
    PSTADE_HAS_TYPE(const_iterator)
    PSTADE_HAS_TYPE(value_type)


} // namespace is_boost_range_detail


// specialize for your range
//
template< class T >
struct is_boost_range_impl :
    boost::mpl::or_<
        is_sequence<T>,
        boost::is_array<T>,
        boost::mpl::and_<
            is_boost_range_detail::has_iterator<T>,
            is_boost_range_detail::has_const_iterator<T>,
            is_boost_range_detail::has_value_type<T>
        >
    >
{ };


template< class T >
struct is_boost_range :
    is_boost_range_impl<
        typename remove_rcv<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
