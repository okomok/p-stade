#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/popped.hpp>


#include <string>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
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
    {
        std::string rng("abcdefg12");
        std::vector<char> expected = std::string("abcdefg")|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            rng|identities(boost::single_pass_traversal_tag())|
                popped|popped,
            expected
        ) );
    }

#if 0 // now empty range not supported
    {
        BOOST_CHECK( boost::empty(std::string()|popped) );
    }
#endif
    {
        std::string str("a");
        BOOST_CHECK( oven::test_empty(str|popped) );
        BOOST_CHECK( oven::test_empty(str|identities(in_forward)|popped) );
        BOOST_CHECK( oven::test_empty(str|identities(in_single_pass)|popped) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
