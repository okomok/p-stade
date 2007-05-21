#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/shared.hpp>


#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/new_delete.hpp>
#include "./core.hpp"
#include <pstade/oven/identities.hpp>


struct xxx :
    std::string,
    private boost::noncopyable
{
    explicit xxx(char const *psz) :
        std::string(psz)
    { }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("0123");

    {
        std::vector<char> expected = std::string("hello, share_range")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            shared(new std::string("hello, share_range")),
            expected
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            shared(new std::string const("hello, share_range")),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(shared(new xxx("0123")), ans) );
    }

    {
        BOOST_CHECK( oven::equals(shared(new xxx("0123")), ans) );
    }

    {
        BOOST_CHECK( oven::equals(shared(pstade::op_new_auto<xxx>()("0123")), ans) );
    }

    {
        BOOST_FOREACH (char ch, shared(new xxx("0123"))) {
           std::cout << ch;
        }
    }
    {
#if 0
        BOOST_FOREACH (char ch, std::string("dangling")|identities) {
            // 'std::string' object doesn't exist anymore. 
            std::cout << ch;
        }
#endif
        BOOST_FOREACH (char ch, shared(new std::string("ok"))|identities) {
            // works fine.
            std::cout << ch;
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
