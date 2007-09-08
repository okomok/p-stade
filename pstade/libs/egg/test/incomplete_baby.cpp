#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/fuse.hpp>
#include <pstade/egg/unfuse.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/uncurry.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct my_baby; // not borns yet.

typedef
    function<my_baby>
my_func;

typedef
    result_of_unfuse<
        result_of_fuse<my_func>::type
    >::type
my_func2;

typedef
    result_of_uncurry<
        result_of_curry2<my_func>::type
    >::type
my_func3;


// borns now.
struct my_baby
{
    template<class Myself, class A1, class A2>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Result, class A1, class A2>
    Result call(A1 &a1, A2 &a2) const
    {
        return a1;
    }
};


void pstade_minimal_test()
{
    {
        int i = 10;
        BOOST_CHECK( &(my_func()(i, 10)) == &i );
        BOOST_CHECK( &(my_func2()(i, 10)) == &i );
        BOOST_CHECK( my_func3()(12, 10) == 12 );
    }
}
