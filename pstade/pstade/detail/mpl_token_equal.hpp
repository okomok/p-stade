#ifndef PSTADE_DETAIL_MPL_TOKEN_EQUAL_HPP
#define PSTADE_DETAIL_MPL_TOKEN_EQUAL_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(1000))
    #define PSTADE_NO_MPL_TOKEN_EQUAL
#else
    #include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#endif


#endif
