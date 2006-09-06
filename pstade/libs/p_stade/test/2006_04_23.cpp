#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/empty.hpp>


// BOOST_MPL_PP_TOKEN_EQUAL_XXX‚Æ‚¢‚¤‚Ì‚ð—pˆÓ‚µ‚È‚­‚Ä‚Í‚¢‚¯‚È‚¢
//
#define BOOST_MPL_PP_TOKEN_EQUAL_left(X) X
#define BOOST_MPL_PP_TOKEN_EQUAL_right(X) X


#define P_STADE_GO_LEFT() \
	"LEFT" \
/**/

#define P_STADE_GO_RIGHT() \
	"RIGHT" \
/**/


#define P_STADE_GO(X) \
	BOOST_PP_IF (BOOST_MPL_PP_TOKEN_EQUAL(X, left), \
		P_STADE_GO_LEFT, \
		P_STADE_GO_RIGHT \
	)() \
/**/


int test_main(int, char*[])
{
	std::cout << P_STADE_GO(left) << std::endl;
	std::cout << P_STADE_GO(right) << std::endl;
	return 0;
}
