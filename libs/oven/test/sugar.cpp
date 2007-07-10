#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/sugar.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <list>
#include <vector>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    using namespace oven::sugar;

    {
        std::string       rng1("12");
        std::list<char>   rng2 = std::string("34")|copied;
        std::vector<char> rng3 = std::string("56")|copied;

        BOOST_CHECK( equals(
             +(rng1 >> rng2 >> rng3) | taken(17),
            std::string("12345612345612345")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
