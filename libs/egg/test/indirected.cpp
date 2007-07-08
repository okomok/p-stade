#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/indirected.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <pstade/result_of.hpp>
#include <boost/preprocessor/facilities/identity.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct op_foo
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};


void pstade_minimal_test()
{
    {
        ::op_foo foo;

        typedef pstade::result_of<op_indirected(::op_foo *)>::type ip_t;
        ip_t ip = PSTADE_EGG_INDIRECTED_RESULT_INITIALIZER(BOOST_PP_IDENTITY(&foo));

        PSTADE_TEST_IS_RESULT_OF((int), ip_t(int, int))

        int r = ip(1, 2);
        BOOST_CHECK( r == 3 );
        r = indirected(&foo)(4, 5);
        BOOST_CHECK( r == 9 );
    }
}
