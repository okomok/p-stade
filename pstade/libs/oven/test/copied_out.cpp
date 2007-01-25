#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/copied_out.hpp>


#include <iterator>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/is_same.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string   in("hello, copied_out!");
        std::string out1;
        std::string out2;
        std::string out3;
        in|copied_out(std::back_inserter(out1));
        in|copied_out(std::back_inserter(out2))|copied_out(std::back_inserter(out3));
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );

        BOOST_CHECK( pstade::is_same(in, in|copied_out(std::back_inserter(out1))) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
