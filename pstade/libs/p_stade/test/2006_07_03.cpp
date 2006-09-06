#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace secret {

    struct XXX
    { };


    template< class Ex >
    void call()
    {
        XXX xxx;
        BOOST_CHECK(false);
    }

}


template< class Ex >
void call()
{ }


template< class Ex >
void test()
{
    call<Ex>();
}


int test_main(int, char*[])
{
    ::test<secret::XXX>();
    return 0;
}
