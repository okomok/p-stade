#ifndef BOOST_EGG_DETAIL_OVERLOADED_CALL_LITTLE_FWD_HPP
#define BOOST_EGG_DETAIL_OVERLOADED_CALL_LITTLE_FWD_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// A quick workaround applying lazy_enable_if to
// `egg::call_little` didn't work; gcc-3.4 has ETI bug around lazy_enable_if.


#include <boost/egg/config.hpp>


#if !defined(BOOST_EGG_NEEDS_OVERLOADED)
    #error This header is needed only with BOOST_EGG_NEEDS_OVERLOADED.
#endif


namespace boost { namespace egg { namespace details {


    template<class Little, class Re, class Void = void>
    struct overloaded_call_little;


} } } // namespace boost::egg::details


#endif
