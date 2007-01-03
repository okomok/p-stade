#ifndef PSTADE_TESTS_HPP
#define PSTADE_TESTS_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_TEST_IS_SAME(X, Y) \
    BOOST_MPL_ASSERT((::boost::is_same< \
        PSTADE_UNPARENTHESIZE(X), \
        PSTADE_UNPARENTHESIZE(Y) \
    >)); \


#define PSTADE_TEST_IS_RESULT_OF(Result, FunCall) \
    PSTADE_TEST_IS_SAME(Result, (::boost::result_of<FunCall>::type)) \
/**/


#endif
