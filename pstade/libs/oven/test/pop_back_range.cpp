#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/pop_back_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/identity_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("abcdefg12");
        std::vector<char> expected = std::string("abcdefg")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|popped_back|popped_back,
            expected
        ) );
    }
    {
        std::string rng("abcdefg12");
        std::vector<char> expected = std::string("abcdefg")|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            rng|identities(boost::forward_traversal_tag())|
                popped_back|popped_back,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
