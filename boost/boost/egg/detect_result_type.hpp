#ifndef BOOST_EGG_DETECT_RESULT_TYPE_HPP
#define BOOST_EGG_DETECT_RESULT_TYPE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Workaround for: http://svn.boost.org/trac/boost/ticket/1317
// Include this header before any Boost headers.


#include <boost/egg/detail/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
    // Place HAS_XXX_TRAIT_DEFs as close as possible.
    #include <boost/lambda/core.hpp>
    #include <boost/utility/result_of.hpp>
#endif


#endif
