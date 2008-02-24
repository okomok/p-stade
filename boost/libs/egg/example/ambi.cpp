

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ambi.hpp>
#include <functional> // plus


#include "./egg_example.hpp"


//[code_example_ambi
struct base_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

result_of_ambi1<base_my_plus>::type const my_plus = BOOST_EGG_AMBI({}); /*< Notice this is not `ambi2` but `ambi1`. >*/

void egg_example()
{
    BOOST_CHECK( my_plus(1, 2) == 3 );
    BOOST_CHECK( ( 1|my_plus(2) ) == 3 );

    std::plus<int> std_plus;
    BOOST_CHECK( ambi1(std_plus)(1, 2) == 3 );
    BOOST_CHECK( ( 1|ambi1(std_plus)(2) ) == 3 );
}
//]
