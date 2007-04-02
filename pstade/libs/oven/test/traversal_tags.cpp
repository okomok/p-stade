#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/traversal_tags.hpp>


#include <string>
#include <pstade/oven/identities.hpp>
#include <pstade/as.hpp>
#include <pstade/oven/transformed.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str;

        BOOST_CHECK( is_single_pass(str|identities(in_single_pass)) );
        BOOST_CHECK( is_forward(str|identities(in_forward)) );
        BOOST_CHECK( is_bidirectional(str|identities(in_bidirectional)) );
        BOOST_CHECK( is_random_access(str) );

        BOOST_CHECK( !is_forward(str|identities(in_single_pass)) );
        BOOST_CHECK( !is_bidirectional(str|identities(in_single_pass)) );
        BOOST_CHECK( !is_random_access(str|identities(in_single_pass)) );

        // RandomAccess*Input* range
        BOOST_CHECK( is_random_access(str|transformed(pstade::as_value)) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
