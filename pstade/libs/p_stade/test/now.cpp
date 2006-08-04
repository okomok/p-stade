#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>


struct xxx :
    private boost::noncopyable
{ };


void foo(xxx const&)
{ }


void test()
{
    ::foo(xxx());
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
