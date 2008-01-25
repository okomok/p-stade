#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// error message check.


#include <pstade/egg/function.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct little_id
{
    template<class Me, class A>
    struct apply { typedef A& type; };

    template<class Re, class A>
    Re call(A& a) const { return a; }
};

typedef function<little_id> T_id;
PSTADE_EGG_CONST((T_id), id) = {{}};


void pstade_minimal_test()
{
    id();
}
