#ifndef PSTADE_EGG_DETAIL_PERFECT_ARITIES_HPP
#define PSTADE_EGG_DETAIL_PERFECT_ARITIES_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <pstade/preprocessor.hpp> // PSTADE_PP_SEQ_RANGE
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY


#define PSTADE_EGG_PERFECT_ARITIES() \
    PSTADE_PP_SEQ_RANGE(0, BOOST_PP_INC(PSTADE_EGG_MAX_ARITY)) \
/**/


#endif
