#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/pack.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/oven/algorithm.hpp>
#include <iterator>
#include <string>
#include <pstade/unparenthesize.hpp>
#include <vector>
#include <pstade/oven/zipped.hpp>
#include <pstade/oven/equals.hpp>
#include <boost/tuple/tuple_comparison.hpp> // DON'T FORGET for Readable test
#include <pstade/egg/to_value.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng1("abc");
        std::vector<int> rng2; { rng2.push_back(1); rng2.push_back(2); rng2.push_back(3); }
        double const rng3[] = { 1.0,2.0,3.0 };


        BOOST_CHECK( pack(rng1) ==
            boost::make_tuple(make_iter_range(rng1))
        );

        BOOST_CHECK( pack(rng1, rng2) ==
            boost::make_tuple(make_iter_range(rng1), make_iter_range(rng2))
        );

        BOOST_CHECK( pack(rng1, rng2, rng3) ==
            boost::make_tuple(make_iter_range(rng1), make_iter_range(rng2), make_iter_range(rng3))
        );

        // rvalue check
        BOOST_CHECK( pack(rng1, rng2, pstade::egg::to_value(make_iter_range(rng3))) ==
            boost::make_tuple(make_iter_range(rng1), make_iter_range(rng2), make_iter_range(rng3))
        );
    }

    {// zipped test
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
            PSTADE_UNPARENTHESIZE((boost::tuple<char&, int&>)) t,
            pack(src0, src1)|zipped
        ) {
            char& ch = boost::get<0>(t);
            if (ch == '4')
                ch = '5';

            int& i = boost::get<1>(t);
            if (i == 4)
                i = 5;
        }
    
        BOOST_CHECK(( equals(src0, ans0) ));
        BOOST_CHECK(( equals(src1, ans1) ));
    }
}
