#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/arg.hpp>


template< class T >
void foo(T& )
{ }


void test()
{
    using namespace pstade;

    ::foo(pstade::arg(1));
    //::foo(1|argued);
}

int test_main(int, char*[])
{
    ::test();
    return 0;
}
