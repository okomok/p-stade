#ifndef PSTADE_IN_UNNAMED_HPP
#define PSTADE_IN_UNNAMED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'stdafx.h' workaround.
// See <boost/bind/placeholders.hpp>.


#include <boost/egg/pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #define PSTADE_IN_UNNAMED static
#else
    #define PSTADE_IN_UNNAMED
#endif


#endif
