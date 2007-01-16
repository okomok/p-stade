#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/identity.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("hello, identity_range");
        std::vector<char> expected = rng|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(rng|identities, expected) );
    }
    {
        std::string str("hello, identity_range");
        BOOST_CHECK(oven::equals(str, str|identities|identities));
    }
    {
        std::string str("hello, identity_range");
        BOOST_CHECK(oven::equals(str, str|identities(boost::single_pass_traversal_tag())));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
