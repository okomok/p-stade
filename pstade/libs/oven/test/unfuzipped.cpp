#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unfuzipped.hpp>
#include <pstade/oven/fuzipped.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/egg/tuple_pack.hpp> // tuple_pack
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/comparison.hpp> // DON'T FORGET for Readable test


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    namespace fusion = boost::fusion;

    {
        std::string rng0("01234567");
        int rng1[] = { 0,1,2,3,4,5,6,7 };

        std::vector<char> ans0 = rng0|copied;
        std::vector<int> ans1  = rng1|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            fusion::at_c<0>(fusion::vector_tie(rng0, rng1)|fuzipped|unfuzipped),
            ans0
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            fusion::at_c<1>(fusion::vector_tie(rng0, rng1)|fuzipped|unfuzipped),
            ans1
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            fusion::at_c<0>(X_make_unfuzipped<boost::mpl::vector2<char&, int&> >()(fusion::vector_tie(rng0, rng1)|fuzipped)),
            ans0
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            fusion::at_c<1>(X_make_unfuzipped<boost::mpl::vector2<char&, int&> >()(fusion::vector_tie(rng0, rng1)|fuzipped)),
            ans1
        ) );
    }
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
            fusion::vector_tie(src0, src1)|fuzipped|elements_c<1>()
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
                fusion::at_c<0>(fusion::vector_tie(src0, src1)|fuzipped|unfuzipped),
                src0
            )
        ));

        BOOST_CHECK((
            oven::equals(
                fusion::at_c<1>(fusion::vector_tie(src0, src1)|fuzipped|unfuzipped),
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
