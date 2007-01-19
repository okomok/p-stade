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
#include <pstade/as.hpp>


using namespace pstade;


template< class A0, class A1 = char >
struct my_type
{
    explicit my_type(A0, A1 = char())
    { }
};


typedef object_generator< my_type< deduce<boost::mpl::_1, deducers::to_value> > > op_make_my_type_v;
PSTADE_CONSTANT(make_my_type_v, (op_make_my_type_v))

typedef object_generator< my_type< deduce<boost::mpl::_1, deducers::as_ref> > > op_make_my_type_r;
PSTADE_CONSTANT(make_my_type_r, (op_make_my_type_r))

typedef object_generator< my_type< deduce<boost::mpl::_1, deducers::to_qualified> > > op_make_my_type_q;
PSTADE_CONSTANT(make_my_type_q, (op_make_my_type_q))


typedef object_generator< my_type< deduce<boost::mpl::_1, deducers::to_value>, deduce<boost::mpl::_2, deducers::to_value, char> > > op_make_my_type_v_d;
PSTADE_CONSTANT(make_my_type_v_d, (op_make_my_type_v_d))


template< class A0 >
struct your_type
{
    explicit your_type(A0, int, int, int)
    { };
};

PSTADE_OBJECT_GENERATOR(make_your_type, (your_type< deduce<_1, to_value> >))



template< class A0 >
struct gcc_bug // Boost1.33 only; Boost1.34 fixed this!
{
    typedef gcc_bug type; // makes 'mpl::quote' need me DefaultConstructible.

    explicit gcc_bug(A0, int)
    { };
};

PSTADE_OBJECT_GENERATOR(make_gcc_bug, (gcc_bug< deduce<_1, to_value> >))


template< class A0 >
struct return_const
{
    explicit return_const(A0)
    { }
};

PSTADE_OBJECT_GENERATOR(make_return_const, (return_const< deduce<_1, to_value> >) const)


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

PSTADE_OBJECT_GENERATOR( make_number312, (number< deduce<_3, to_value>, deduce<_1, to_value>, deduce<_2, to_value> >) )
PSTADE_OBJECT_GENERATOR( make_number111, (number< deduce<_1, to_value>, deduce<_1, to_value>, deduce<_1, to_value> >) )
PSTADE_OBJECT_GENERATOR( make_number213, (number< deduce<_2, to_value>, deduce<_1, to_value>, deduce<_3, to_value> >) )


struct H
{
    typedef int hello;
};

template< class H >
struct get_hello
{
    typedef typename H::hello type;
};

template< class A0, class A1 = typename A0::hello >
struct needs_all_param
{
    explicit needs_all_param(A0, A1 = typename A0::hello())
    { }
};

template< class A0, class A1 >
struct deduce_to_hello :
    boost::mpl::eval_if< boost::is_same<A1, void>,
        get_hello<A0>,
        boost::mpl::identity<A1>
    >
{ };

typedef object_generator< needs_all_param< deduce<boost::mpl::_1, deducers::to_value>, deduce_to_hello<boost::mpl::_1, boost::mpl::_2> > > op_make_nap;
#if !defined(__GNUC__) // GCC3.4.4; internal compiler error: in lookup_member, at cp/search.c:1296
    PSTADE_CONSTANT(make_nap, (op_make_nap))
#endif


template< class A0 >
struct must_mutable
{
    BOOST_MPL_ASSERT_NOT((boost::is_const<A0>));
    explicit must_mutable(A0) { }
};

PSTADE_OBJECT_GENERATOR(make_must_mutable, (must_mutable<_1>))


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

#if !defined(__GNUC__) // GCC3.4.4; internal compiler error: in lookup_member, at cp/search.c:1296
    {
        needs_all_param<H, int> x = ::make_nap(H());
        needs_all_param<H> y = ::make_nap(H());
    }
#endif
    {
        int i = 0; // non-const
        ::make_must_mutable(i);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
