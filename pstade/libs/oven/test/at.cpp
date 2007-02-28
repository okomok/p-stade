
#define NDEBUG

#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/at.hpp>


#include <string>
#include <pstade/oven/checked.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");
        BOOST_CHECK( at(str, 0) == 'f' );
        BOOST_CHECK( at(str, 4) == '4' );
        BOOST_CHECK( (str|at(0)) == 'f' );
        BOOST_CHECK( (str|at(4)) == '4' );

        try {
            at(str|checked, 70);
        }
        catch(std::out_of_range) {
            return;
        }
        BOOST_CHECK(false);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
