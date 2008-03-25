

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/perfect.hpp>
#include <string>


#include "./egg_example.hpp"


//[code_example_perfect
struct imperfect
{
    template<class FunCall>
    struct result;

    template<class Fun, class A>
    struct result<Fun(A &)>
    {
        typedef A &type;
    };

    template<class A>
    A & operator()(A &a) const
    {
        return a;
    }
};

void egg_example()
{
    BOOST_CHECK( perfect(imperfect())(3) == 3 );
}
//]
