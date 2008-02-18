#ifndef BOOST_EGG_DETAIL_IS_CONVERTIBLE_HPP
#define BOOST_EGG_DETAIL_IS_CONVERTIBLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See the implementation of `boost::enable_if_convertible`.
// msvc-7.1 occasionally fails regardless of SFINAE without this.


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/egg/detail/boost_workaround.hpp>


namespace boost { namespace egg { namespace details {


    template<class From, class To>
    struct is_convertible :
        boost::is_convertible<From, To>
    { };


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    template<class To>
    struct is_convertible<To, To> :
        mpl::true_
    { };
#endif


} } } // namespace boost::egg::details


#endif
