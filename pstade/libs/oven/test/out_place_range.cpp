#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
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
    using namespace pstade;
    using namespace oven;

    std::list<char> lst;
    oven::copy(std::string("cfbadehg"), garlic::back_inserter(lst));

    oven::sort(lst|out_placed);
    BOOST_CHECK( oven::equals(lst, std::string("abcdefgh")) );

    // oven::sort(lst|identities);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
