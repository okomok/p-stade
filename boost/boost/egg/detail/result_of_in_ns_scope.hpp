#ifndef BOOST_EGG_DETAIL_RESULT_OF_IN_NS_SCOPE_HPP
#define BOOST_EGG_DETAIL_RESULT_OF_IN_NS_SCOPE_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Used with "../specified.hpp".
// This is required only in namespace scope.
// See "./vc7_1_result_of.hpp" in detail.


#include <boost/preprocessor/seq/enum.hpp>
#include <boost/egg/pstade/boost_workaround.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include <boost/egg/pstade/unparenthesize.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1

    #include <boost/preprocessor/seq/size.hpp>
    #include "./vc7_1_result_of.hpp"

    #define BOOST_EGG_RESULT_OF_IN_NS_SCOPE(F, ArgSeq) \
        typename pstade::egg::detail_vc7_1::BOOST_PP_CAT(result_of, BOOST_PP_SEQ_SIZE(ArgSeq))< \
            PSTADE_UNPARENTHESIZE_TPL(F), BOOST_PP_SEQ_ENUM(ArgSeq) \
        >::type \
    /**/

    #define BOOST_EGG_CONST_REF(A) \
        pstade::egg::detail_vc7_1::const_ref< A > \
    /**/

#else

    #define BOOST_EGG_RESULT_OF_IN_NS_SCOPE(F, ArgSeq) \
        typename pstade::result_of< \
            PSTADE_UNPARENTHESIZE_TPL(F)(BOOST_PP_SEQ_ENUM(ArgSeq)) \
        >::type \
    /**/

    #define BOOST_EGG_CONST_REF(A) \
        A const& \
    /**/

#endif


#endif
