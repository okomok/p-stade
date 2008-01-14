#ifndef PSTADE_APPLE_IS_DEQUE_HPP
#define PSTADE_APPLE_IS_DEQUE_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./deque_fwd.hpp"


namespace pstade { namespace apple {


namespace is_deque_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


    template< class T, class Alloc >
    struct aux< std::deque<T, Alloc> > :
        boost::mpl::true_
    { };


} // namespace is_deque_detail


template< class T >
struct is_deque :
    is_deque_detail::aux<
        typename boost::remove_cv<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
