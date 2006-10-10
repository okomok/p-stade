#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/out_place_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/identity_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::list<char> lst;
    oven::copy(std::string("cfbadehg"), std::back_inserter(lst));

    oven::sort(lst|identities|out_placed);
    BOOST_CHECK( oven::equals(lst, std::string("abcdefgh")) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
