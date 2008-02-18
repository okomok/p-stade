

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/perfect.hpp>
#include "./egg_test.hpp"


#include <pstade/test.hpp>
#include <boost/preprocessor/facilities/identity.hpp>


#include "./using_egg.hpp"


struct nonperfect
{
    typedef int result_type;

    template<class A>
    int operator()(A& i) const
    {
        return i;
    }
};


void egg_test()
{
    {
        BOOST_CHECK( perfect(::nonperfect())(10) == 10 );
    }
    {
        typedef pstade::result_of<T_perfect(::nonperfect)>::type perf_t;
        PSTADE_TEST_IS_RESULT_OF((int), perf_t(int))

        perf_t perf = BOOST_EGG_PERFECT({});
        BOOST_CHECK( perf(10) == 10 );
    }
}
