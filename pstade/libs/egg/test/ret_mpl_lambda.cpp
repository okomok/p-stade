#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ret.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <pstade/egg/plus.hpp>
#include <boost/type_traits/add_const.hpp>


// Notice the total specialization in class is illegal.
template<class A0 = void, class A1 = void, class A2 = void>
struct add_const_apply;

template<>
struct add_const_apply<>
{
    typedef char type;
};

template<class A0, class A1>
struct add_const_apply<A0, A1>
{
    BOOST_MPL_ASSERT_NOT((boost::is_same<A0, void>));
    typedef A0 const type;
};

struct add_const
{
    template<class A0 = void, class A1 = void, class A2 = void>
    struct apply :
        ::add_const_apply<A0, A1, A2>
    {};
};


namespace egg = pstade::egg;
using namespace egg;

BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_plus(int, int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_plus(double, double)>::type, double>));


typedef result_of_ret<T_plus, nullary_meta< ::add_const > >::type T_my_plus;
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus()>::type, char>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus(int, int)>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus(double, double)>::type, double const>));

typedef result_of_ret<T_plus, boost::add_const<boost::mpl::_1> >::type T_my_plus2;
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus2(int, int)>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus2(double, double)>::type, double const>));


struct T_always_a
{
    char operator()() const { return 'a'; }
};
PSTADE_POD_CONSTANT((T_always_a), always_a) = {};


void pstade_minimal_test()
{
    {
        int x = egg::ret< nullary_meta< ::add_const > >(plus)(1, 2);
        BOOST_CHECK(x == 3);
    }
    {
        int x = egg::ret<boost::add_const<boost::mpl::_1> >(plus)(1, 2);
        BOOST_CHECK(x == 3);
    }
    {
        char x = egg::ret< nullary_meta< ::add_const > >(always_a)();
        BOOST_CHECK(x == 'a');
    }
}
