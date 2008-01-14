#ifndef PSTADE_TEST_HPP
#define PSTADE_TEST_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_TEST_IS_SAME(X, Y) \
    BOOST_MPL_ASSERT((::boost::is_same< \
        PSTADE_UNPARENTHESIZE(X), \
        PSTADE_UNPARENTHESIZE(Y) \
    >)); \


#define PSTADE_TEST_IS_RESULT_OF(Result, FunCall) \
    BOOST_MPL_ASSERT((::boost::is_same< \
        PSTADE_UNPARENTHESIZE(Result), \
        pstade::result_of<FunCall>::type \
    >)); \
/**/


#endif
