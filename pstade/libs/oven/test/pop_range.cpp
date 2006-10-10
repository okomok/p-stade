#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/pop_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string rng("0123456789");
    {
        std::vector<char> expected = std::string("12345678")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|popped(1,1),
            expected
        ) );
    }
    {
        std::vector<char> expected = std::string("345")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|popped(1,1)|popped(2,3),
            expected
        ) );
    }

    {
        std::string src("0123456789");
        {
            BOOST_CHECK( oven::equals(
                src|popped(1, 1),
                std::string("12345678")
            ) );
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
