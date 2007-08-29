#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/compose2.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/identity.hpp>


struct my_minus
{
    typedef int result_type;

    int operator()(int i, int j) const
    {
        return i - j;
    }
};

struct my_negate
{
    typedef int result_type;

    int operator()(int i) const
    {
        return -i;
    }
};


void pstade_minimal_test()
{
    namespace egg = pstade::egg;

    {
        BOOST_CHECK( egg::compose2(my_minus(), my_negate(), egg::identity)(2) == (-2)-2);
    }
}
