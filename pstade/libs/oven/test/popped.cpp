#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/popped.hpp>


#include <string>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("abcdefg12");
        std::vector<char> expected = std::string("abcdefg")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|popped|popped,
            expected
        ) );
    }
    {
        std::string rng("abcdefg12");
        std::vector<char> expected = std::string("abcdefg")|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            rng|identities(boost::forward_traversal_tag())|
                popped|popped,
            expected
        ) );
    }
#if 0 // now empty range not supported
    {
        BOOST_CHECK( boost::empty(std::string()|popped) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
