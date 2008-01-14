#ifndef PSTADE_APPLE_IS_BOOST_RANGE_HPP
#define PSTADE_APPLE_IS_BOOST_RANGE_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Will be deprecated; after all, this is useless.
// <boost/egg/copy_assign.hpp> is much better.


#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/egg/pstade/enable_if.hpp>
#include <boost/egg/pstade/has_xxx.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./is_sequence.hpp"


namespace pstade { namespace apple {


namespace is_boost_range_detail {


    PSTADE_HAS_TYPE(iterator)
    PSTADE_HAS_TYPE(const_iterator)


} // namespace is_boost_range_detail


// specialize for your range
//
template< class T, class = enabler >
struct is_boost_range_impl :
    boost::mpl::or_<
        is_sequence<T>,
        boost::is_array<T>,
        boost::mpl::and_<
            is_boost_range_detail::has_iterator<T>,
            is_boost_range_detail::has_const_iterator<T>
        >
    >
{ };


template< class T >
struct is_boost_range :
    is_boost_range_impl<
        typename boost::remove_cv<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
