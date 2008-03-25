#ifndef BOOST_EGG_PREPROCESSOR_SEQ_REPEAT_HPP
#define BOOST_EGG_PREPROCESSOR_SEQ_REPEAT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/seq_cycle.hpp>


// A -> (A)(A)..(A)
#define BOOST_EGG_PP_SEQ_REPEAT(A, Size) \
    BOOST_EGG_PP_SEQ_CYCLE((A), Size) \
/**/


#endif
