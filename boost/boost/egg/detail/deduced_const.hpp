#ifndef BOOST_EGG_DETAIL_DEDUCED_CONST_HPP
#define BOOST_EGG_DETAIL_DEDUCED_CONST_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #include <boost/type_traits/add_const.hpp>
    // Note "::boost::add_const" won't work.
    #define BOOST_EGG_DEDUCED_CONST(T) typename boost::add_const< T >::type
#else
    #define BOOST_EGG_DEDUCED_CONST(T) T const
#endif


#endif
