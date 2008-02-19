#ifndef BOOST_EGG_DETAIL_PERFECT_ARITIES_HPP
#define BOOST_EGG_DETAIL_PERFECT_ARITIES_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/preprocessor/seq_range.hpp>


#define BOOST_EGG_PERFECT_ARITIES() \
    BOOST_EGG_PP_SEQ_RANGE(0, BOOST_PP_INC(BOOST_EGG_MAX_ARITY)) \
/**/


#endif
