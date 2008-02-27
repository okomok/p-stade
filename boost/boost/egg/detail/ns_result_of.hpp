#ifndef BOOST_EGG_DETAIL_NS_RESULT_OF_HPP
#define BOOST_EGG_DETAIL_NS_RESULT_OF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See "./ns_result_of1.hpp"


#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/unparen.hpp>
#include <boost/egg/detail/ns_const_ref.hpp> // inclusion guaranteed


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

    #include <boost/preprocessor/tuple/rem.hpp>
    #include <boost/egg/detail/vc7_1_result_of.hpp>

    #define BOOST_EGG_NS_RESULT_OF(F, ArgArray) \
        typename boost::egg::detail_vc7_1::result_of< \
            BOOST_EGG_UNPAREN_TPL(F), BOOST_PP_TUPLE_REM_CTOR ArgArray \
        >::type \
    /**/

#else

    #include <boost/egg/result_of.hpp>

    #define BOOST_EGG_NS_RESULT_OF(F, ArgArray) \
        typename boost::egg::result_of_< \
            BOOST_EGG_UNPAREN_TPL(F) BOOST_PP_ARRAY_DATA(ArgArray) \
        >::type \
    /**/

#endif


#endif
