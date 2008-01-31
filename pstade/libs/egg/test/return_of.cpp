#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/return_of.hpp>
#include <pstade/lightweight_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/egg/apply.hpp>


using pstade::egg::return_of;
using pstade::egg::F_ptr;
using pstade::egg::T_apply;
using pstade::egg::apply;


struct T_plus
{
    typedef int result_type;

    result_type operator()(int i, int j) const
    {
        return i + j;
    }
};

T_plus const plus = {};

struct T_negate
{
    typedef int result_type;

    result_type operator()(int i) const
    {
        return -i;
    }
};

T_negate const negate = {};


int minus(int i, int j)
{
    return i - j;
}



BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(int, int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(int, T_plus(int, int))>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(T_plus(int, int), int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(T_plus(int, int), T_plus(int, int))>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(T_plus(int, int), T_plus(int, T_plus(int, int)))>::type, int>));

BOOST_MPL_ASSERT((boost::is_same<return_of<T_negate(int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(T_negate(int), T_plus(int, int))>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_plus(T_plus(int, int), T_negate(int))>::type, int>));

BOOST_MPL_ASSERT((boost::is_same<return_of<T_apply(F_ptr<int(*)(int, int)>, int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<return_of<T_apply(F_ptr<int(int, int)>, int)>::type, int>));




void pstade_lightweight_test()
{
    {
        return_of<T_plus(T_plus(int, int), int)>::type
            r = plus(plus(1, 2), 3);
        BOOST_CHECK( r == 1+2+3 );
    }
    {
        return_of<T_plus(T_plus(int, T_negate(int)), int)>::type
            r = plus(plus(1, negate(2)), 3);
        BOOST_CHECK( r == 1+(-2)+3 );
    }
    {
        return_of<T_apply(F_ptr<int(*)(int, int)>, int)>::type
            r = apply(&minus, 3, 2);
        BOOST_CHECK( r == 1 );
    }
    {
        return_of<T_apply(F_ptr<int(int, int)>, int)>::type
            r = apply(&minus, 3, 2);
        BOOST_CHECK( r == 1 );
    }
}
