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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");

        BOOST_CHECK( *next(boost::begin(str)) == '1' );
        BOOST_CHECK( *prior(boost::end(str))  == 'b' );

        BOOST_CHECK( *next(boost::begin(str), 3) == '3' );
        BOOST_CHECK( *prior(boost::end(str), 2)  == '5' );

        BOOST_CHECK( *next_begin(str) == '1' );
        BOOST_CHECK( *prior_end(str)  == 'b' );

        BOOST_CHECK( *next_begin(str, 3) == '3' );
        BOOST_CHECK( *prior_end(str, 2)  == '5' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
