#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/functional.hpp>


void test()
{
    BOOST_CHECK( pstade::always(3)() == 3 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
