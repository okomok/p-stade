#ifndef PSTADE_DETECT_RESULT_TYPE_HPP
#define PSTADE_DETECT_RESULT_TYPE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Workaround for: http://svn.boost.org/trac/boost/ticket/1317
// Include this header before any Boost headers.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    // Place HAS_XXX_TRAIT_DEFs as close as possible.
    #include <boost/lambda/core.hpp>
    #include <boost/utility/result_of.hpp>
#endif


#endif
