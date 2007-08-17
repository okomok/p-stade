#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>

#include <pstade/egg/function_by_value.hpp>
using namespace pstade::egg;


//[code_value_identity
struct baby_value_identity
{
    template<class Myself, class A>
    struct apply
    {
        /*<< `A` is a "plain" type. >>*/
        typedef A type;
    };

    /*<< `Result` is `A`. >>*/
    template<class Result, class A>
    Result call(A a) const
    {
        return a;
    }
};

typedef function_by_value<baby_value_identity> op_value_identity;
op_value_identity const value_identity = {{}};

void test()
{
    BOOST_CHECK( value_identity(1) == 1 );
}
//]


void pstade_minimal_test()
{
    test();
}
