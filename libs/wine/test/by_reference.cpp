#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/by_reference.hpp>


template< class T >
void foo(T& )
{ }


void test()
{
    using namespace pstade;

    ::foo(1|by_reference);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
