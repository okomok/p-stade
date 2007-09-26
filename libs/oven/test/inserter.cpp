#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/inserter.hpp>
#include <pstade/minimal_test.hpp>


#include <vector>
#include <list>
#include <algorithm> // copy
#include <pstade/oven/equals.hpp>


namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    std::string const src("abcdefg");

    {
        std::vector<char> v;
        std::copy(src.begin(), src.end(), back_inserter|=v);
        BOOST_CHECK( equals(v, src) );
    }
    {
        std::list<char> v;
        std::copy(src.begin(), src.end(), front_inserter|=v);
        BOOST_CHECK( equals(v, std::string("gfedcba")) );
    }
    {
        std::list<char> v;
        std::copy(src.begin(), src.end(), inserter(v.end())|=v);
        BOOST_CHECK( equals(v, src) );
    }
}
