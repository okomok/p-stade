#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/repeated.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/taken.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("1111");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            '1'|repeated(4),
            expected
        ) );
    }
    {
        std::string ans("1111");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            '1'|repeated|taken(4),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(
            'A'|repeated(6),
            std::string("AAAAAA")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
