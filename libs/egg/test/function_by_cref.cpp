#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function_by_cref.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <memory> // auto_ptr
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>


#include <pstade/pod_constant.hpp>
#include <pstade/unparenthesize.hpp>

    #define PSTADE_EGG_FUNCTION_BY_CREF(O, B) \
        typedef pstade::egg::function_by_cref<PSTADE_UNPARENTHESIZE(B)> BOOST_PP_CAT(op_, O); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_, O)), O) = { { } }; \
    /**/


struct baby_foo
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef A0 const type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0 const& a0, A1 const& a1) const
    {
        return a0 + a1;
    }

    template< class Myself, class A0 >
    struct apply<Myself, A0>
    {
        typedef A0 const type;
    };

    template< class Result, class A0 >
    Result call(A0 const& a0) const
    {
        return a0;
    }

    typedef char nullary_result_type;

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

PSTADE_EGG_FUNCTION_BY_CREF(foo, (baby_foo))

PSTADE_TEST_IS_RESULT_OF((int) const, op_foo(int, int))
PSTADE_TEST_IS_RESULT_OF((int) const, op_foo(int&, int))
PSTADE_TEST_IS_RESULT_OF((int) const, op_foo(int const&, int))
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>) const, op_foo(std::auto_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((char), op_foo())


struct baby_big_arity
{
    template<class Myself, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {
        typedef A0 const& type;
    };

    template<class Result, class A0>
    Result call(A0 const& a0, ...) const
    {
        return a0;
    }
};

PSTADE_EGG_FUNCTION_BY_CREF(big_arity, (baby_big_arity))


void pstade_minimal_test()
{
    {
        pstade::result_of<op_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == 3 );
    }
    {
        pstade::result_of<op_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int const i = 3;
        BOOST_CHECK( &(big_arity(i,1,2,3,4,5,6,7,8,9)) == &i );
        BOOST_CHECK( big_arity(3,1,2,3,4,5,6,7,8,9) == 3 );
    }
}
