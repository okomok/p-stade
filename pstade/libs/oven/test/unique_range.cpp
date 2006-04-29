#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unique_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
    int ans2[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };

    {

        BOOST_CHECK((
            oven::equals( oven::make_unique_range(src), ans2)
        ));
    }


    {
        BOOST_CHECK((
            oven::equals( src|uniqued|reversed|reversed, ans2)
        ));

		BOOST_FOREACH (int i, src|uniqued|reversed)  {
			std::cout << i << ',';
		}
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
