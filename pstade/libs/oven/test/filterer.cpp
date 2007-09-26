#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/filterer.hpp>
#include <pstade/minimal_test.hpp>


#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/stream_writer.hpp>


std::stringstream g_ss;


bool is_not_e(char ch)
{
    return ch != 'e';
}


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string const src("hello,filterer");
    std::string const ans("hllo,filtrr");
    {
        g_ss.str("");
        std::copy(src.begin(), src.end(), filterer(&is_not_e)|=stream_writer|=g_ss);
        BOOST_CHECK( oven::equals(g_ss.str(), ans) );
    }
    {
        std::vector<char> v(11);
        std::copy(src.begin(), src.end(), filterer(&is_not_e)|=v.begin());
        BOOST_CHECK( oven::equals(v, ans) );
    }
}
