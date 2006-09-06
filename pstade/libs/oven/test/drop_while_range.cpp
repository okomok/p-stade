#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/drop_while_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


void test()
{
    using namespace pstade;
    using namespace boost;
    using namespace oven;

    {
        std::string src("11111234516313!");

        BOOST_CHECK( oven::equals(
            src|dropped_while(lambda::_1 == '1'),
            std::string("234516313!")
        ) );

        BOOST_CHECK( oven::equals(
            src|dropped_while(lambda::_1 == '9'),
            src
        ) );

        BOOST_CHECK( oven::equals(
            src|dropped_while(lambda::_1 != '9'),
            std::string("")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
