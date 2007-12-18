#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/pointer.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/test.hpp>
#include <pstade/pod_constant.hpp>


namespace egg = pstade::egg;
using namespace egg;



struct T_my_inc
{
    // typedef int result_type; // no result_type.

    int operator()(int i) const
    {
        return i+1;
    }
};

PSTADE_POD_CONSTANT((T_my_inc), my_inc) = {};


struct T_my_plus
{
    typedef int result_type;

    int operator()(int i, int j) const
    {
        return i+j;
    }
};

PSTADE_POD_CONSTANT((T_my_plus), my_plus) = {};


struct T_my_two
{
    typedef int result_type;

    int operator()() const
    {
        return 2;
    }
};

PSTADE_POD_CONSTANT((T_my_two), my_two) = {};


struct id0;
struct id1;


void pstade_minimal_test()
{
    {
        int r = egg::pointer<int(int), id0>(my_inc)(11);
        BOOST_CHECK(r == 12);
    }
    {
        result_of_pointer<T_my_plus, int(int, int), id0>::type fp = egg::pointer<int(int, int), id0>(my_plus);
        int r = fp(1, 2);
        BOOST_CHECK(r == 3);
    }
    {
        pstade::result_of<X_pointer<int(int, int), id0>(T_my_plus const&)>::type fp = egg::pointer<int(int, int), id0>(my_plus);
        int r = (*fp)(1, 2);
        BOOST_CHECK(r == 3);
    }
    {
        int r = egg::pointer<boost::use_default(int, int), id1>(my_plus)(1, 2);
        BOOST_CHECK(r == 3);
    }
    {
        int r = egg::pointer<int(), id0>(my_two)();
        BOOST_CHECK(r == 2);
    }
    {
        int r = egg::pointer<boost::use_default(), id1>(my_two)();
        BOOST_CHECK(r == 2);
    }
}
