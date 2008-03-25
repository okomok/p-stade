#ifndef BOOST_EGG_DETAIL_NS_RESULT_OF1_HPP
#define BOOST_EGG_DETAIL_NS_RESULT_OF1_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Namespace Scope result_of for msvc-7.1 bug workaround.
// `F` can't be const-qualified.


#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/ns_const_ref.hpp> // inclusion guaranteed
#include <boost/egg/detail/unparen.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

    #include <boost/egg/detail/vc7_1_result_of1.hpp>

    #define BOOST_EGG_NS_RESULT_OF1(F, A) \
        typename boost::egg::detail_vc7_1::result_of1< BOOST_EGG_UNPAREN_TPL(F), A >::type \
    /**/

#else

    #include <boost/egg/result_of.hpp>

    #define BOOST_EGG_NS_RESULT_OF1(F, A) \
        typename boost::egg::result_of_< BOOST_EGG_UNPAREN_TPL(F)(A) >::type \
    /**/

#endif


#endif
