#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>



//[code_result_of_tutorial1
#include <boost/utility/result_of.hpp>
using boost::result_of;

struct T_plus
{
    typedef int result_type;

    result_type operator()(int i, int j) const
    {
        return i + j;
    }
};

void test_lvalue()
{
    int i = 2;
    result_of<T_plus(int &, int)>::type r = T_plus()(i, 3);
    BOOST_CHECK( r == 5 );
}
//]


//[code_result_of_tutorial2
void test_chain()
{
    int const i = 3;
    result_of<
        T_plus(result_of<T_plus(int, int)>::type, int const &)
    >::type r
        = T_plus()(T_plus()(1, 2), i);
}
//]


//[code_result_of_tutorial3
T_plus const plus = {};

void test_const()
{
    result_of<T_plus const(int, int)>::type r = plus(2, 3);
    BOOST_CHECK( r == 5 );
}
//]


//[code_result_of_tutorial4
void test_operatable()
{
    result_of<T_plus(int, int)>::type r = plus(2, 3);
    BOOST_CHECK( r == 5 );
}
//]


void pstade_minimal_test()
{
    test_lvalue();
    test_const();
    test_chain();
    test_operatable();
}
