#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/take_while_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("11111234516313!");
        std::vector<char> expected = std::string("11111")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|taken_while(lambda::_1 == '1'),
            expected
        ) );  
    }
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
