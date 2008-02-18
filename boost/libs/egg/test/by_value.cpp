

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_value.hpp>
#include "./egg_test.hpp"


#include <string>
#include <memory> // auto_ptr
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>


#include <pstade/pod_constant.hpp>
#include <pstade/unparenthesize.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>

    #define BOOST_EGG_FUNCTION_BY_VALUE(O, B) \
        typedef pstade::egg::function<PSTADE_UNPARENTHESIZE(B), pstade::egg::by_value> BOOST_PP_CAT(T_, O); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, O)), O) = { { } }; \
    /**/


struct little_foo
{
    template< class Me, class A0, class A1 = void >
    struct apply
    {
        BOOST_MPL_ASSERT_NOT((boost::is_reference<A0>));
        BOOST_MPL_ASSERT_NOT((boost::is_const<A0>));
        typedef A0 type;
    };

    template< class Re, class A0, class A1 >
    Re call(A0 a0, A1 a1) const
    {
        return a0 + a1;
    }

    template< class Me, class A0 >
    struct apply<Me, A0>
    {
        BOOST_MPL_ASSERT_NOT((boost::is_reference<A0>));
        BOOST_MPL_ASSERT_NOT((boost::is_const<A0>));
        typedef A0 type;
    };

    template< class Re, class A0 >
    Re call(A0 a0) const
    {
        return a0;
    }

    typedef char nullary_result_type;

    template< class Re >
    Re call() const
    {
        return '0';
    }
};

BOOST_EGG_FUNCTION_BY_VALUE(foo, (little_foo))

PSTADE_TEST_IS_RESULT_OF((int), T_foo(int, int))
PSTADE_TEST_IS_RESULT_OF((int), T_foo(int&, int))
PSTADE_TEST_IS_RESULT_OF((int), T_foo(int const&, int))
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>), T_foo(std::auto_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((char), T_foo())


std::auto_ptr<int> make_auto_ptr()
{
    return std::auto_ptr<int>(new int(3));
}


struct little_big_arity
{
    template<class Me, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {

        BOOST_MPL_ASSERT_NOT((boost::is_reference<A0>));
        BOOST_MPL_ASSERT_NOT((boost::is_const<A0>));
        typedef A0 type;
    };

    template<class Re, class A0>
    Re call(A0 a0, ...) const
    {
        return a0;
    }
};

BOOST_EGG_FUNCTION_BY_VALUE(big_arity, (little_big_arity))



void egg_test()
{
    {
        pstade::result_of<T_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == 3 );
    }
    {
        pstade::result_of<T_foo(std::auto_ptr<int>)>::type x = foo(make_auto_ptr());
        BOOST_CHECK( *x == 3 );
    }
    {
        pstade::result_of<T_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        BOOST_CHECK( big_arity(3,1,2,3,4,5,6,7,8,9) == 3 );
    }
}
