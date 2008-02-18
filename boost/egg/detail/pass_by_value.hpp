#ifndef BOOST_EGG_DETAIL_PASS_BY_VALUE_HPP
#define BOOST_EGG_DETAIL_PASS_BY_VALUE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace boost { namespace egg { namespace details {


    template<class T>
    struct pass_by_value :
        boost::remove_cv<typename boost::decay<T>::type>
    { };


} } } // namespace boost::egg::details


#endif
