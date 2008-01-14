#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/indirect.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <pstade/result_of.hpp>
#include <boost/preprocessor/facilities/identity.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct T_foo
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};


result_of_indirect<T_indirect const *>::type const
    inindirect = PSTADE_EGG_INDIRECT(&indirect);


void pstade_minimal_test()
{
    {
        ::T_foo foo;

        typedef pstade::result_of<T_indirect(::T_foo *)>::type ip_t;
        ip_t ip = PSTADE_EGG_INDIRECT_L &foo PSTADE_EGG_INDIRECT_R;

        PSTADE_TEST_IS_RESULT_OF((int), ip_t(int, int))

        int r = ip(1, 2);
        BOOST_CHECK( r == 3 );
        r = indirect(&foo)(4, 5);
        BOOST_CHECK( r == 9 );
    }
    {
        ::T_foo foo;
        int volatile i = 1;
        int r = inindirect(&foo)(i, 2);
        BOOST_CHECK( r == 3 );
    }
}
