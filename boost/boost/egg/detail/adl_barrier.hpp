#ifndef BOOST_EGG_DETAIL_ADL_BARRIER_HPP
#define BOOST_EGG_DETAIL_ADL_BARRIER_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>


#define BOOST_EGG_ADL_BARRIER(Id) \
    namespace BOOST_EGG_ADL_BARRIER_name(Id) { \
    } \
    using namespace BOOST_EGG_ADL_BARRIER_name(Id); \
    namespace BOOST_EGG_ADL_BARRIER_name(Id) \
/**/


#define BOOST_EGG_ADL_BARRIER_name(Id) \
    BOOST_PP_CAT(boost_egg_adl_barrier_of_, Id) \
/**/


#endif
