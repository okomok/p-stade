#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/next_prior.hpp>


#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/compose.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");

        BOOST_CHECK( *next(begin(str)) == '1' );
        BOOST_CHECK( *prior(end(str))  == 'b' );

        BOOST_CHECK( *next(begin(str), 3) == '3' );
        BOOST_CHECK( *prior(end(str), 2)  == '5' );

        BOOST_CHECK( *pstade::compose(next, begin)(str) == '1' );
        BOOST_CHECK( *pstade::compose(prior, end)(str)  == 'b' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
