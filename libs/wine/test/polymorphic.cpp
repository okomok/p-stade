#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/polymorphic.hpp>
#include <boost/version.hpp>
#include <pstade/functional.hpp>


using namespace pstade;


void test()
{
#if BOOST_VERSION >= 103500
    {
        int i = 10;
        BOOST_CHECK( polymorphic(identity)(i) == 10 );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
