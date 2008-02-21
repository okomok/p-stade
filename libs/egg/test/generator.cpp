

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/generator.hpp>
#include "./egg_test.hpp"
#include <boost/egg/detail/unparen.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/egg/detail/unparen.hpp>
#include "./check_is_result_of.hpp"



namespace deducers = boost::egg;


#define EGG_generator_def(G, L) \
    namespace BOOST_PP_CAT(pstade_egg_generator_workarea_of_, G) { \
        using namespace boost::mpl::placeholders; \
        using namespace boost::egg; \
        typedef boost::egg::generator<BOOST_EGG_UNPAREN(L)>::type op; \
    } \
    typedef BOOST_PP_CAT(pstade_egg_generator_workarea_of_, G)::op BOOST_PP_CAT(T_, G); \
    BOOST_EGG_CONST((BOOST_PP_CAT(T_, G)), G) = BOOST_EGG_GENERATOR(); \
/**/


template< class A0 >
struct your_type
{
    explicit your_type(A0, int, int, int)
    { };
};

EGG_generator_def(make_your_type, (your_type< deduce<_1, as_value> >))
CHECK_IS_RESULT_OF(your_type<int>, T_make_your_type(int&))


using namespace boost::egg;


template< class A0, class A1 = char >
struct my_type
{
    explicit my_type(A0, A1 = char())
    { }
};


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_value> >, boost::use_default, boost::use_default, char >::type T_make_my_type_v;
T_make_my_type_v const make_my_type_v = BOOST_EGG_GENERATOR();
CHECK_IS_RESULT_OF(my_type<int>, T_make_my_type_v(int&))
CHECK_IS_RESULT_OF(char, T_make_my_type_v())


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_ref> > >::type T_make_my_type_r;
T_make_my_type_r const make_my_type_r = BOOST_EGG_GENERATOR();
CHECK_IS_RESULT_OF(my_type<int const&>, T_make_my_type_r(int))
CHECK_IS_RESULT_OF(my_type<int&>, T_make_my_type_r(int&))


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_qualified> > >::type T_make_my_type_q;
T_make_my_type_q const make_my_type_q = BOOST_EGG_GENERATOR();
CHECK_IS_RESULT_OF(my_type<int const>, T_make_my_type_q(int))
CHECK_IS_RESULT_OF(my_type<int>, T_make_my_type_q(int&))


typedef generator< my_type< deduce<boost::mpl::_1, deducers::as_value>, deduce<boost::mpl::_2, deducers::as_value, char> > >::type T_make_my_type_v_d;
T_make_my_type_v_d const make_my_type_v_d = BOOST_EGG_GENERATOR();



template< class A0 >
struct gcc_bug // Boost1.33 only; Boost1.34 fixed this!
{
    typedef gcc_bug type; // makes 'mpl::quote' need me DefaultConstructible.

    explicit gcc_bug(A0, int)
    { };
};

EGG_generator_def(make_gcc_bug, (gcc_bug< deduce<_1, as_value> >))


template< class A0 >
struct return_const
{
    explicit return_const(A0)
    { }
};

typedef
    boost::egg::generator<return_const< deduce<boost::mpl::_1, as_value> const>::type
T_make_return_const;
T_make_return_const const make_return_const = BOOST_EGG_GENERATOR();


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

EGG_generator_def( make_number312, (number< deduce<_3, as_value>, deduce<_1, as_value>, deduce<_2, as_value> >) )
EGG_generator_def( make_number111, (number< deduce<_1, as_value>, deduce<_1, as_value>, deduce<_1, as_value> >) )
EGG_generator_def( make_number213, (number< deduce<_2, as_value>, deduce<_1, as_value>, deduce<_3, as_value> >) )


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

typedef generator< needs_all_param< deduce<boost::mpl::_1, deducers::as_value>, deduce_to_hello<boost::mpl::_1, boost::mpl::_2> > >::type T_make_nap;
#if !BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(3)) // GCC3.4.4; internal compiler error: in lookup_member, at cp/search.c:1296
    T_make_nap const make_nap = BOOST_EGG_GENERATOR();
#endif


// Without dummy_to_lambda, the perfect overload resolution would instantiate it with const.
template< class A0 >
struct must_mutable
{
    BOOST_MPL_ASSERT_NOT((boost::is_const<A0>));
    explicit must_mutable(A0) { }
};

EGG_generator_def(make_must_mutable, (must_mutable<_1>))


void egg_test()
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
        BOOST_MPL_ASSERT(( boost::is_const<boost::egg::result_of_< ::T_make_return_const(int) >::type> ));
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

#if !BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(3)) // GCC3.4.4; internal compiler error: in lookup_member, at cp/search.c:1296
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
