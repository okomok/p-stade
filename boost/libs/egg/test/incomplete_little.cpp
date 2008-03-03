

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/uncurry.hpp>
#include "./egg_test.hpp"


#include <boost/utility/addressof.hpp>


#include "./using_egg.hpp"


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
    template<class Me, class A1, class A2, class A3, class A4>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Re, class A1, class A2, class A3, class A4>
    Re call(A1 &a1, A2 &a2, A3 &a3, A4 &a4) const
    {
        if (!&a1)
            my_func()(a1, a2, a3, a4); // call myself.
        return a1;
    }
};


void egg_test()
{
    {
        int i = 10;
        BOOST_CHECK( boost::addressof(my_func()(i, 2,3,4)) == &i );
        BOOST_CHECK( boost::addressof(my_func2()(i, 2,3,4)) == &i );
        BOOST_CHECK( my_func3()(12, 2,3,4) == 12 );
    }
}
