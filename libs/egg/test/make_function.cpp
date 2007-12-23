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
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/by_perfect.hpp>


#include <boost/utility/addressof.hpp>


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


PSTADE_TEST_IS_RESULT_OF((function<baby>), T_make_function(baby))


void pstade_minimal_test()
{
    baby b;
    int i = 10;
    BOOST_CHECK( make_function(b)(1) == 1 );
    BOOST_CHECK( boost::addressof(X_make_function<by_value>()(b)(i)) != &i );
}
