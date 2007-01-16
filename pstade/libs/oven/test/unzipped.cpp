#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/unzipped.hpp>
#include <pstade/oven/zipped.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/pack.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string src0("0123456");
        std::string ans0("0123556");

        std::vector<int> src1; {
            int tmp[] = { 0,1,2,3,4,5,6 };
            oven::copy(tmp, std::back_inserter(src1));
        }
        std::vector<int> ans1; {
            int tmp[] = { 0,1,2,3,5,5,6 };
            oven::copy(tmp, std::back_inserter(ans1));
        }

        BOOST_FOREACH (
            int& i,
            src0|pstade::packed(src1)|zipped|unzipped_at_c<1>()
        ) {
            if (i == 4)
                i = 5;
        }
    
        BOOST_CHECK(( oven::equals(src0, src0) )); // not changed
        BOOST_CHECK(( oven::equals(src1, ans1) ));
    }

    {
        std::string src0("0123456");
        std::vector<int> src1; {
            int tmp[] = { 0,1,2,3,4,5,6 };
            oven::copy(tmp, std::back_inserter(src1));
        }

        BOOST_CHECK((
            oven::equals(
                boost::get<0>(src0|pstade::packed(src1)|zipped|unzipped),
                src0
            )
        ));

        BOOST_CHECK((
            oven::equals(
                boost::get<1>(src0|pstade::packed(src1)|zipped|unzipped),
                src1
            )
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
