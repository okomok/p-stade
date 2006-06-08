#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/comma_protect.hpp>


#include <map>
#include <utility>
#include <boost/foreach.hpp>


void test()
{
	using namespace pstade;

    BOOST_FOREACH (
    	comma_protect<void(std::pair<int, int>)>::type p,
    	comma_protect<void(std::map<int, int>)>::type()
	) {
		BOOST_CHECK((p, false));
	}
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
