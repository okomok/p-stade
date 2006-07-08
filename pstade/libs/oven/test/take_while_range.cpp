#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/take_while_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/algorithms.hpp>
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
            src|taken_while(lambda::_1 == '1'),
            std::string("11111")
        ) );

        BOOST_CHECK( oven::equals(
            src|taken_while(lambda::_1 == '9'),
            std::string("")
        ) );

        BOOST_CHECK( oven::equals(
            src|taken_while(lambda::_1 != '9'),
            src
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
