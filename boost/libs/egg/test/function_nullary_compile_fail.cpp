

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// error message check.


#include <boost/egg/function.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>


#include "./using_egg.hpp"


struct little_id
{
    template<class Me, class A>
    struct apply { typedef A& type; };

    template<class Re, class A>
    Re call(A& a) const { return a; }
};

typedef function<little_id> T_id;
BOOST_EGG_CONST((T_id), id) = {{}};


void egg_test()
{
    id();
}
