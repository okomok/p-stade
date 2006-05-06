#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/statement.hpp>


#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/instance.hpp>



PSTADE_INSTANCE(int, x, value)

PSTADE_STATEMENT(Update,
	x_() = 3;
	x_() += 1;
)

void test()
{
    BOOST_CHECK(x == 4);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
