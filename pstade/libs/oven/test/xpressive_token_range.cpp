#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/xpressive_token_range.hpp>


#include <string>
#include <vector>
#include <boost/xpressive/xpressive.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        boost::xpressive::sregex re = '$';
        bool f = false;
        if (f) {
            std::string("This is a string of tokens.")|xpressive_tokenized(re);
            std::string("This is a string of tokens.")|xpressive_tokenized(re, -1);
            std::string("This is a string of tokens.")|xpressive_tokenized(re, std::vector<int>(), boost::xpressive::regex_constants::match_default);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
