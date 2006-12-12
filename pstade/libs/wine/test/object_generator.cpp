#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/object_generator.hpp>
#include <pstade/constant.hpp>


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/unparenthesize.hpp>


using namespace pstade;


template< class A0, class A1 = char >
struct my_type
{
    explicit my_type(A0, A1 = char())
    { }
};


typedef object_generator< my_type< deduce_to_value<from_1> > > op_make_my_type_v;
PSTADE_CONSTANT(make_my_type_v, op_make_my_type_v)

typedef object_generator< my_type< deduce_to_reference<from_1> > > op_make_my_type_r;
PSTADE_CONSTANT(make_my_type_r, op_make_my_type_r)

typedef object_generator< my_type< deduce_to_qualified<from_1> > > op_make_my_type_q;
PSTADE_CONSTANT(make_my_type_q, op_make_my_type_q)


typedef object_generator< my_type< deduce_to_value<from_1>, deduce_to_value<from_2, char> > > op_make_my_type_v_d;
PSTADE_CONSTANT(make_my_type_v_d, op_make_my_type_v_d)


template< class A0 >
struct your_type
{
    explicit your_type(A0, int, int, int)
    { };
};

PSTADE_OBJECT_GENERATOR(make_your_type, your_type< deduce_to_value<from_1> >)



template< class A0 >
struct gcc_bug // Boost1.33 only; Boost1.34 fixed this!
{
    typedef gcc_bug type; // makes 'mpl::quote' need me DefaultConstructible.

    explicit gcc_bug(A0, int)
    { };
};

PSTADE_OBJECT_GENERATOR(make_gcc_bug, gcc_bug< deduce_to_value<from_1> >)


template< class A0 >
struct return_const
{
    explicit return_const(A0)
    { }
};

PSTADE_OBJECT_GENERATOR(make_return_const, const return_const< deduce_to_value<from_1> >)


template< class A0, class A1, class A2 >
struct number
{
    template< class T0, class T1, class T2 >
    explicit number(T0, T1, T2)
    { }
};

struct A {};
struct B {};
struct C {};

PSTADE_OBJECT_GENERATOR( make_number312, PSTADE_UNPARENTHESIZE((number< deduce_to_value<from_3>, deduce_to_value<from_1>, deduce_to_value<from_2> >)) )
PSTADE_OBJECT_GENERATOR( make_number111, PSTADE_UNPARENTHESIZE((number< deduce_to_value<from_1>, deduce_to_value<from_1>, deduce_to_value<from_1> >)) )
PSTADE_OBJECT_GENERATOR( make_number213, PSTADE_UNPARENTHESIZE((number< deduce_to_value<from_2>, deduce_to_value<from_1>, deduce_to_value<from_3> >)) )
// PSTADE_OBJECT_GENERATOR( make_number_,   PSTADE_UNPARENTHESIZE((number< deduce_to_value<from_>, deduce_to_value<from_>, deduce_to_value<from_> >)) ) // not supported by MPL.


void test()
{
    {
        my_type<int> x = ::make_my_type_v(5);
    }
    {
        my_type<int const&> x = ::make_my_type_r(5);
    }
    {
        my_type<int const> x = ::make_my_type_q(5);
    }
    {
        my_type<int> x = ::make_my_type_v_d(5);
    }

    {
        your_type<char> x = ::make_your_type('a', 1, 2, 3);
    }

    {
        gcc_bug<int> x = ::make_gcc_bug(0, 1);
    }

    {
        return_const<int> x = ::make_return_const(1);
        BOOST_MPL_ASSERT(( boost::is_const<boost::result_of< ::op_make_return_const(int) >::type> ));
    }

    {
        number<C, A, B> x = ::make_number312(A(), B(), C());
    }
    {
        number<A, A, A> x = ::make_number111(A(), B(), C());
    }
    {
        number<B, A, C> x = ::make_number213(A(), B(), C());
    }
    {
        //number<A, B, C> x = ::make_number_(A(), B(), C());
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
