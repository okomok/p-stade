#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/detail/is_nullary.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/detail/is_binary.hpp>


void test()
{
	BOOST_CHECK( BOOST_PP_IS_NULLARY( () )          );
	BOOST_CHECK( BOOST_PP_IS_NULLARY( ()(x,y) )     );
	BOOST_CHECK(!BOOST_PP_IS_NULLARY( a )           );
	BOOST_CHECK(!BOOST_PP_IS_NULLARY( ~ )           );

	BOOST_CHECK( BOOST_PP_IS_UNARY( (x) )           );
   	BOOST_CHECK( BOOST_PP_IS_UNARY( ((x,y)) )       );
	BOOST_CHECK( BOOST_PP_IS_UNARY( (x)(y) )        );
	BOOST_CHECK(!BOOST_PP_IS_UNARY( 3 )             );
	BOOST_CHECK(!BOOST_PP_IS_UNARY( ~ )             );
	// BOOST_CHECK(!BOOST_PP_IS_UNARY( (x,y) )      ); ‚±‚¤‚¢‚¤Žg‚¢•û‚Í‚Å‚«‚È‚¢

	BOOST_CHECK( BOOST_PP_IS_BINARY( (x,y) )        );
	BOOST_CHECK( BOOST_PP_IS_BINARY( (x,y)() )      );
	BOOST_CHECK( BOOST_PP_IS_BINARY( (x,y) )        );
	BOOST_CHECK(!BOOST_PP_IS_BINARY( _ )            );
	BOOST_CHECK(!BOOST_PP_IS_BINARY( ~ )            );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
