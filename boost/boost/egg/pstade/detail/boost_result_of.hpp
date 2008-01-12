#ifndef PSTADE_DETAIL_BOOST_RESULT_OF_HPP
#define PSTADE_DETAIL_BOOST_RESULT_OF_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>


#if BOOST_VERSION < 103600

    // <boost/preprocessor.hpp> is too big.
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_params.hpp>
    #if !defined(BOOST_PREPROCESSOR_HPP)
        #define BOOST_PREPROCESSOR_HPP
        #include <boost/utility/result_of.hpp>
        #undef  BOOST_PREPROCESSOR_HPP
    #else
        #include <boost/utility/result_of.hpp>
    #endif

#else

    #include <boost/utility/result_of.hpp>

#endif


#endif
