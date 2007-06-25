#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/xpressive_matches.hpp>


#include <string>
#include <vector>
#include <boost/xpressive/xpressive.hpp>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string input("This is his face");
        boost::xpressive::sregex re = +boost::xpressive::_w; // a word

        bool f = false;
        if (f) {
            input|xpressive_matches(re);
            input|xpressive_matches(re, boost::xpressive::regex_constants::match_default);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
