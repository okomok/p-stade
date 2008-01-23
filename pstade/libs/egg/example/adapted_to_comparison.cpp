#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/adapted_to.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


//[code_adapted_to_comparison
struct base_plus
{
    int id;

    typedef int result_type;

    result_type operator()(int x, int y) const
    {
        return x + y;
    }
};

typedef result_of_curry2<base_plus>::type T_curried_plus;
T_curried_plus const curried_plus777 = PSTADE_EGG_CURRY2({777});
T_curried_plus const curried_plus999 = PSTADE_EGG_CURRY2({999});

bool operator==(T_curried_plus const &left, T_curried_plus const &right)
{
    return egg::adapted_to<base_plus>(left).id == egg::adapted_to<base_plus>(right).id;
}

void test()
{
    BOOST_CHECK( curried_plus777(4)(9) == 4+9 );
    BOOST_CHECK( egg::adapted_to<base_plus>(curried_plus777).id == 777);
    BOOST_CHECK( curried_plus777 == curried_plus777 );
    BOOST_CHECK(!(curried_plus777 == curried_plus999) );
}
//]


void pstade_minimal_test()
{
    test();
}
