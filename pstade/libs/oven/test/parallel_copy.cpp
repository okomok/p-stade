#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_copy.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/oven/equals.hpp>
#include <string>
#include <vector>


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[21] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        std::vector<int> b(25);
        BOOST_CHECK( equals(a, make_iter_range(b.begin(), parallel_copy(5, a, b.begin()))) );
    }
    {
        int a[21] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        std::vector<int> b(21);
        BOOST_CHECK( equals(a, make_iter_range(b.begin(), parallel_copy(0, a, b.begin()))) ); // default grainsize
    }
    {
        std::string b("0123401234");
        std::string a("**********");
        BOOST_CHECK( a.end() == parallel_copy(5, b, a.begin()) );
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::string b("01234012");
        std::string a("********");
        BOOST_CHECK( a.end() == parallel_copy(5, b, a.begin()) );
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::string b;
        std::vector<char> a;
        BOOST_CHECK( a.begin() == parallel_copy(1, b, a.begin()) );
        BOOST_CHECK( a.empty() );
        BOOST_CHECK( a.begin() == parallel_copy(100, b, a.begin()) );
        BOOST_CHECK( a.empty() );
    }
}
