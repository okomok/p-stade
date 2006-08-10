#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr


std::auto_ptr<int> new_int()
{
    return std::auto_ptr<int>(new int());
}


void test()
{
    std::auto_ptr<int const> ap(::new_int());
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
