#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>


#include <iostream>
#include <string>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/functional.hpp>
#include <pstade/oven.hpp>


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;


    std::string src("1223444445");

    copy(src|adjacent_filtered(pstade::equal_to), to_stream(std::cout));

    BOOST_CHECK( equals(
        src|adjacent_filtered(regular(lambda::_1 == lambda::_2))|uniqued,
        std::string("24")
    ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
