#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <pstade/oven/fuzipped.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/tuple.hpp> // tuple_pack
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copy_range.hpp>


#include <boost/fusion/sequence/adapted/boost_tuple.hpp>
#include <boost/fusion/sequence/comparison.hpp> // DON'T FORGET for Readable test
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/generation/vector_tie.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int b1[10] = { 6,2,2,1,37,4,2,1,3,6 };
        std::string b2("6819385738");

        typedef boost::fusion::vector<int&, char&> tt;
        std::vector<tt> a;
        a.push_back(boost::fusion::vector_tie(b1[0], b2[0]));
        a.push_back(boost::fusion::vector_tie(b1[1], b2[1]));
        a.push_back(boost::fusion::vector_tie(b1[2], b2[2]));
        a.push_back(boost::fusion::vector_tie(b1[3], b2[3]));
        a.push_back(boost::fusion::vector_tie(b1[4], b2[4]));
        a.push_back(boost::fusion::vector_tie(b1[5], b2[5]));
        a.push_back(boost::fusion::vector_tie(b1[6], b2[6]));
        a.push_back(boost::fusion::vector_tie(b1[7], b2[7]));
        a.push_back(boost::fusion::vector_tie(b1[8], b2[8]));
        a.push_back(boost::fusion::vector_tie(b1[9], b2[9]));

        test::random_access_constant(
            pstade::tuple_pack(b1, b2)|fuzipped|const_refs,
            a
        );
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
            PSTADE_UNPARENTHESIZE((boost::fusion::vector<char&, int&>)) t,
            pstade::tuple_pack(src0, src1)|fuzipped
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

#include <pstade/minimal_test.hpp>

void pstade_minimal_test() { }

#endif
