#ifndef BOOST_EGG_DETAIL_PLAIN_HPP
#define BOOST_EGG_DETAIL_PLAIN_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace egg { namespace details {


    template<class T>
    struct plain :
        remove_cv<typename remove_reference<T>::type>
    { };


    template<class T>
    struct is_plain :
        is_same<T, typename plain<T>::type>
    { };


} } } // namespace boost::egg::details


#endif
