
// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date: 2004-09-03 00:41:37 +0900 (Fri, 03 Sep 2004) $
// $Revision: 24874 $

#include <pstade/pp_token_equal.hpp>

#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/debug/assert.hpp>

#define AUX_ASSERT_EQUAL(x, y) \
    BOOST_PP_ASSERT( PSTADE_PP_TOKEN_EQUAL(x, y) ) \
/**/

#define AUX_ASSERT_NOT_EQUAL(x, y) \
    BOOST_PP_ASSERT( BOOST_PP_NOT( PSTADE_PP_TOKEN_EQUAL(x, y) ) ) \
/**/

#define PSTADE_PP_TOKEN_EQUAL_apple(x) x
#define PSTADE_PP_TOKEN_EQUAL_orange(x) x

AUX_ASSERT_NOT_EQUAL( apple, abc )
AUX_ASSERT_NOT_EQUAL( abc, apple )
AUX_ASSERT_NOT_EQUAL( apple, orange )
AUX_ASSERT_NOT_EQUAL( orange, apple )

AUX_ASSERT_EQUAL( apple, apple )
AUX_ASSERT_EQUAL( orange, orange )


int main() {}
