#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unzip_range.hpp>
#include <pstade/oven/zip_range.hpp>


#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string src0("0123456");
        std::string ans0("0123556");

        std::vector<int> src1; {
            int tmp[] = { 0,1,2,3,4,5,6 };
            oven::copy(tmp, garlic::back_inserter(src1));
        }
        std::vector<int> ans1; {
            int tmp[] = { 0,1,2,3,5,5,6 };
            oven::copy(tmp, garlic::back_inserter(ans1));
        }

        BOOST_FOREACH (
            int& i,
            boost::tie(src0, src1)|zipped|unzipped<1>()
        ) {
            if (i == 4)
                i = 5;
        }
    
        BOOST_CHECK(( oven::equals(src0, src0) )); // not changed
        BOOST_CHECK(( oven::equals(src1, ans1) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
