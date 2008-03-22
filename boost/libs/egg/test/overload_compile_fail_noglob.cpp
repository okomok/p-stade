

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/overload.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/vector.hpp>
#include "./using_egg.hpp"


struct T_fun1
{
    typedef int result_type;

    result_type operator()(int const &i , int j) const
    {
        return i + j;
    }
};


typedef
    boost::mpl::vector<
        T_fun1(int const &, int)
    >
overload_set;

typedef result_of_overload<overload_set>::type T_fun;
T_fun fun;



void egg_test()
{
    {
        fun(1);
        fun();
    }
}
