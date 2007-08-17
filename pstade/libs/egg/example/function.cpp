#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>

#include <pstade/egg/function.hpp>
using namespace pstade::egg;


//[code_second_argument
struct baby_second_argument
{
    template<class Myself, class A1, class A2>
    struct apply
    {
        /*<< Don't forget add reference. >>*/
        typedef A2 &type;
    };

    /*<< `Result` is `A2 &`. >>*/
    template<class Result, class A1, class A2>
    Result call(A1 &a1, A2 &a2) const
    {
        return a2;
    }
};

typedef function<baby_second_argument> op_second_argument;

/*<< A blaced initialization is ok, because `op_second_argument` is POD. >>*/
op_second_argument const second_argument = {{}};

void test()
{
    int i = 2;
    BOOST_CHECK( &(second_argument(1, i)) == &i );
    BOOST_CHECK( second_argument(1, i) == 2 );
}
//]


void pstade_minimal_test()
{
    test();
}
