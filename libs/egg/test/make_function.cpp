#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/make_function.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct baby
{
    template<class Myself, class A>
    struct apply
    {
        typedef A& type;
    };

    template<class Result, class A>
    Result call(A& a) const
    {
        return a;
    }
};


PSTADE_TEST_IS_RESULT_OF((function<baby>), op_make_function(baby))


void pstade_minimal_test()
{
    BOOST_CHECK( make_function(baby())(1) == 1 );
}
