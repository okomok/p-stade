#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <pstade/oven/tests.hpp>
#include <pstade/oven/fuzipped.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./core.hpp"
#include <pstade/pack.hpp>

#include <boost/fusion/sequence/adapted/boost_tuple.hpp>
#include <boost/fusion/sequence/comparison.hpp> // DON'T FORGET for Readable test
#include <boost/fusion/sequence/intrinsic/at.hpp>

void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

#if 0 // fusion::vector template constructor eats operator-bracket proxy.
     {
        std::string rng0("0123");
        int rng1[] = { 0,1,2,3 };

        typedef boost::fusion::vector<char, int> tt;
        std::vector<tt> expected;
        expected.push_back(tt('0', 0));
        expected.push_back(tt('1', 1));
        expected.push_back(tt('2', 2));
        expected.push_back(tt('3', 3));

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng0|pstade::packed(rng1)|fuzipped,
            expected
        ) );
    }
    {
        std::string rng0("0123");
        int rng1[] = { 0,1,2,3 };
        std::string rng2("ABCD");

        typedef boost::fusion::vector<char, int, char> tt;
        std::vector<tt> expected;
        expected.push_back(tt('0', 0, 'A'));
        expected.push_back(tt('1', 1, 'B'));
        expected.push_back(tt('2', 2, 'C'));
        expected.push_back(tt('3', 3, 'D'));

       BOOST_CHECK( oven::test_RandomAccess_Readable(
            boost::tuples::tie(rng0, rng1, rng2)|fuzipped,
            expected
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng0|pstade::packed(rng1, rng2)|fuzipped,
            expected
        ) );
    }
#endif 
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
            PSTADE_UNPARENTHESIZE((boost::fusion::vector<char&, int&>)) t,
            pstade::pack(src0, src1)|fuzipped
        ) {
            char& ch = boost::fusion::at_c<0>(t);
            if (ch == '4')
                ch = '5';

            int& i = boost::fusion::at_c<1>(t);
            if (i == 4)
                i = 5;
        }
    
        BOOST_CHECK(( oven::equals(src0, ans0) ));
        BOOST_CHECK(( oven::equals(src1, ans1) ));

    }
    {
        // tuple contains value.
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

        boost::fusion::vector< std::string, std::vector<int> > z(src0, src1);
        BOOST_FOREACH (
            PSTADE_UNPARENTHESIZE((boost::fusion::vector2<char&, int&>)) t,
            z|fuzipped
        ) {
            char& ch = boost::fusion::at_c<0>(t);
            if (ch == '4')
                ch = '5';

            int& i = boost::fusion::at_c<1>(t);
            if (i == 4)
                i = 5;
        }
    
        BOOST_CHECK(( oven::equals(boost::fusion::at_c<0>(z), ans0) ));
        BOOST_CHECK(( oven::equals(boost::fusion::at_c<1>(z), ans1) ));
    }
}


#else
void test() { }
#endif


int test_main(int, char*[])
{
    ::test();
    return 0;
}
