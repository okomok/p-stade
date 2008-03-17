#ifndef BOOST_EGG_DETAIL_NEST_NAMES_HPP
#define BOOST_EGG_DETAIL_NEST_NAMES_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// using-directive is useless after all.


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/preprocessor/cat3.hpp>


namespace boost { namespace egg {

    struct nest_names;

} }


#define BOOST_EGG_NEST_NAMES \
    /* using */ boost::egg::nest_names \
    BOOST_PP_REPEAT_FROM_TO(0, BOOST_PP_INC(BOOST_EGG_MAX_ARITY), BOOST_EGG_NEST_NAMES_using_nest, ~) \
    BOOST_PP_REPEAT_FROM_TO(0, BOOST_EGG_MAX_ARITY, BOOST_EGG_NEST_NAMES_using_N_, ~) \
/**/

    #define BOOST_EGG_NEST_NAMES_using_nest(Z, N, Unused) ; using boost::egg::BOOST_PP_CAT(nest, N)
    #define BOOST_EGG_NEST_NAMES_using_N_(Z, N, Unused) ; using boost::egg::BOOST_EGG_PP_CAT3(_, N, _)


#endif
