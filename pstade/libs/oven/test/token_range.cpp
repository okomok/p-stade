#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/token_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/concatenate_range.hpp>
#include <pstade/oven/tests.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string input("This is his face");
        boost::regex re("\\w+");
        bool f = false;
        if (f) {
            input|tokenized(re);
            input|tokenized(re, -1);
            input|tokenized(re, std::vector<int>(), boost::regex_constants::match_default);
        }

        BOOST_CHECK( oven::equals(input|tokenized(re)|concatenated, std::string("Thisishisface") ) );
        BOOST_CHECK( oven::test_forward(input|tokenized(re)|concatenated) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
