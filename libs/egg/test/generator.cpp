#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/generator.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/test.hpp>



namespace deducers = pstade::egg;


#define PSTADE_EGG_OBJECT_GENERATOR(G, L) \
    namespace BOOST_PP_CAT(pstade_egg_generator_workarea_of_, G) { \
        using namespace boost::mpl::placeholders; \
        using namespace pstade::egg; \
        typedef pstade::egg::generator<PSTADE_UNPARENTHESIZE(L)>::type op; \
    } \
    typedef BOOST_PP_CAT(pstade_egg_generator_workarea_of_, G)::op BOOST_PP_CAT(op_, G); \
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_, G)), G) = PSTADE_EGG_GENERATOR_INITIALIZER(); \
/**/


#if 0

template<class Lambda, class How = boost::use_default, class NullaryResult = boost::use_default>
struct generator
{
    typedef 
        pstade::egg::function< pstade::egg::baby::generator<Lambda, How, NullaryResult> >
    type;
};

#endif


template< class A0 >
struct your_type
{
    explicit your_type(A0, int, int, int)
    { };
};

PSTADE_EGG_OBJECT_GENERATOR(make_your_type, (your_type< deduce<_1, as_value> >))
PSTADE_TEST_IS_RESULT_OF((your_type<int>), op_make_your_type(int&))


using namespace pstade::egg;


template< class A0, class A1 = char >
struct my_type
{
    explicit my_type(A0, A1 = char())
    { }
};


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_value> >, boost::use_default, char >::type op_make_my_type_v;
op_make_my_type_v const make_my_type_v = PSTADE_EGG_GENERATOR_INITIALIZER();
PSTADE_TEST_IS_RESULT_OF((my_type<int>), op_make_my_type_v(int&))
PSTADE_TEST_IS_RESULT_OF((char), op_make_my_type_v())


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_reference> > >::type op_make_my_type_r;
op_make_my_type_r const make_my_type_r = PSTADE_EGG_GENERATOR_INITIALIZER();
PSTADE_TEST_IS_RESULT_OF((my_type<int const&>), op_make_my_type_r(int))
PSTADE_TEST_IS_RESULT_OF((my_type<int&>), op_make_my_type_r(int&))


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_qualified> > >::type op_make_my_type_q;
op_make_my_type_q const make_my_type_q = PSTADE_EGG_GENERATOR_INITIALIZER();
PSTADE_TEST_IS_RESULT_OF((my_type<int const>), op_make_my_type_q(int))
PSTADE_TEST_IS_RESULT_OF((my_type<int>), op_make_my_type_q(int&))


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_value>, deduce<boost::mpl::_2, deducers::as_value, char> > >::type op_make_my_type_v_d;
op_make_my_type_v_d const make_my_type_v_d = PSTADE_EGG_GENERATOR_INITIALIZER();



template< class A0 >
struct gcc_bug // Boost1.33 only; Boost1.34 fixed this!
{
    typedef gcc_bug type; // makes 'mpl::quote' need me DefaultConstructible.

    explicit gcc_bug(A0, int)
    { };
};

PSTADE_EGG_OBJECT_GENERATOR(make_gcc_bug, (gcc_bug< deduce<_1, as_value> >))


template< class A0 >
struct return_const
{
    explicit return_const(A0)
    { }
};

PSTADE_EGG_OBJECT_GENERATOR(make_return_const, (return_const< deduce<_1, as_value> >) const)


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

PSTADE_EGG_OBJECT_GENERATOR( make_number312, (number< deduce<_3, as_value>, deduce<_1, as_value>, deduce<_2, as_value> >) )
PSTADE_EGG_OBJECT_GENERATOR( make_number111, (number< deduce<_1, as_value>, deduce<_1, as_value>, deduce<_1, as_value> >) )
PSTADE_EGG_OBJECT_GENERATOR( make_number213, (number< deduce<_2, as_value>, deduce<_1, as_value>, deduce<_3, as_value> >) )


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

typedef generator< needs_all_param< deduce<boost::mpl::_1, deducers::as_value>, deduce_to_hello<boost::mpl::_1, boost::mpl::_2> > >::type op_make_nap;
#if !defined(__GNUC__) // GCC3.4.4; internal compiler error: in lookup_member, at cp/search.c:1296
    op_make_nap const make_nap = PSTADE_EGG_GENERATOR_INITIALIZER();
#endif


template< class A0 >
struct must_mutable
{
    BOOST_MPL_ASSERT_NOT((boost::is_const<A0>));
    explicit must_mutable(A0) { }
};

PSTADE_EGG_OBJECT_GENERATOR(make_must_mutable, (must_mutable<_1>))


void pstade_minimal_test()
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
        BOOST_MPL_ASSERT(( boost::is_const<pstade::result_of< ::op_make_return_const(int) >::type> ));
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
