#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/uncurry.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/deduced_form.hpp> // check it.


#include <boost/utility/addressof.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct my_little; // not borns yet.

typedef
    function<my_little>
my_func;

typedef
    result_of_unfuse<
        result_of_fuse<my_func>::type
    >::type
my_func2;

typedef
    result_of_uncurry<
        result_of_curry4<my_func>::type
    >::type
my_func3;


// borns now.
struct my_little
{
    template<class Myself, class A1, class A2, class A3, class A4>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Result, class A1, class A2, class A3, class A4>
    Result call(A1 &a1, A2 &, A3 &, A4 &) const
    {
        return a1;
    }
};


void pstade_minimal_test()
{
    {
        int i = 10;
        BOOST_CHECK( boost::addressof(my_func()(i, 2,3,4)) == &i );
        BOOST_CHECK( boost::addressof(my_func2()(i, 2,3,4)) == &i );
        BOOST_CHECK( my_func3()(12, 2,3,4) == 12 );
    }
}
