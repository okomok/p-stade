#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/sub_set.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("abcde");

    oven::sub_set<std::string> ss1(src);
    
    BOOST_CHECK( oven::equals(ss1, src) );

    std::string::iterator its[] = { boost::begin(src), boost::begin(src)+2, boost::begin(src)+4 };

    oven::sub_set<std::string> ss2(its);

    BOOST_CHECK( oven::equals(ss2, std::string("ace")) );

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
