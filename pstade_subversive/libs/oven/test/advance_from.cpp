#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/advance_from.hpp>


#include <string>
#include <pstade/oven/begin_end.hpp>
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");

        BOOST_CHECK( *advance_from(begin(str), 1) == '1' );
        BOOST_CHECK( *advance_from(end(str), -1)  == 'b' );

        BOOST_CHECK( *advance_from(begin(str), 3) == '3' );
        BOOST_CHECK( *advance_from(end(str), -2)  == '5' );
    }
    {
        std::string str("f12344513215b");

        BOOST_CHECK( *advance_from(begin(str|identities(in_bidirectional)), 1) == '1' );
        BOOST_CHECK( *advance_from(end(str|identities(in_bidirectional)), -1)  == 'b' );

        BOOST_CHECK( *advance_from(begin(str|identities(in_bidirectional)), 3) == '3' );
        BOOST_CHECK( *advance_from(end(str|identities(in_bidirectional)), -2)  == '5' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
