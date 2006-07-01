#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/token_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/algorithms.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        boost::regex re("\\s+");
        bool f = false;
        if (f) {
            std::string("This is a string of tokens.")|tokenized(re);
            std::string("This is a string of tokens.")|tokenized(re, -1);
            std::string("This is a string of tokens.")|tokenized(re, std::vector<int>(), boost::regex_constants::match_default);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
