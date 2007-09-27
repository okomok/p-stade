#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/apply.hpp>
#include <pstade/minimal_test.hpp>


using namespace pstade::egg;


struct op_my_foo
{
    typedef int result_type;

    int operator()() const
    {
        return 12;
    }

    int operator()(int &x) const
    {
        return x;
    }

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

op_my_foo const my_foo = {};


void pstade_minimal_test()
{
    {
        int i = 1;
        BOOST_CHECK( apply(my_foo) == 12 );
        BOOST_CHECK( apply(my_foo, i) == i );
        BOOST_CHECK( apply(my_foo, i, 2) == 3 );
    }
}

