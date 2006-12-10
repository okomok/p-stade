#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/object_generator.hpp>


#include <boost/mpl/placeholders.hpp>
#include <boost/tuple/tuple.hpp>


using namespace pstade;


#if 0 // LambdaExpression rejected.

template< class A0 >
struct my_type
{
    explicit my_type(A0)
    { }
};


typedef boost::mpl::placeholders::_1 object_1;
typedef boost::mpl::placeholders::_2 object_2;


typedef object_generator< my_type<object_1> > v_gen_t;
typedef object_generator< my_type<object_1>, object_by_value > v_gen_t_;
typedef object_generator< my_type<object_1>, object_by_qualifier > c_gen_t;


template< class A0, class A1 >
struct your_type
{
    typedef your_type type; // will break down GCC3.4.

    explicit your_type(A0, A1)
    { }
};


// GCC3.4 requires your_type to be DefaultConstructible
// if you put nested 'type' in 'your_type', so we define...
template< class A0, class A1 >
struct make_your_type
{
    typedef your_type<A0, A1> type;
};

typedef object_generator< make_your_type<object_1, object_2> > yv_gen_t;
typedef object_generator< make_your_type<object_1, object_2>, object_by_value, object_by_value > yv_gen_t_;
typedef object_generator< make_your_type<object_1, object_2>, object_by_qualifier, object_by_value > ycv_gen_t;

#endif


// Workaround for above situation using macro.
template< class A0, class A1 >
struct our_type
{
    typedef our_type type;

    explicit our_type(A0, A1)
    { }
};

PSTADE_OBJECT_GENERATOR(make_our_type, our_type, (object_by_qualifier)(object_by_value))


PSTADE_OBJECT_GENERATOR_WITH_A_DEFAULT(my_tie, const boost::tuples::tuple,
    (object_by_reference)(object_by_reference)(object_by_reference)(object_by_reference)(object_by_reference), boost::tuples::null_type)


void test()
{
#if 0 // LambdaExpression rejected.
    {
        my_type<int> o = ::v_gen_t()(3);
        my_type<int> o_ = ::v_gen_t_()(3);
    }
    {
        int x = 3;
        my_type<int> o = ::c_gen_t()(x);
    }
    {
        my_type<int const> o = ::c_gen_t()(3);
    }
    {
        int const x = 3;
        my_type<int const> o = ::c_gen_t()(x);
    }

    {
        your_type<int, int> o = ::yv_gen_t()(3, 4);
        your_type<int, int> o_ = ::yv_gen_t_()(3, 4);
    }
    {
        int x = 3;
        your_type<int, int> o = ::ycv_gen_t()(x, 3);
    }
    {
        your_type<int const, int> o = ::ycv_gen_t()(3, 3);
    }

    {
        int const x = 3;
        your_type<int const, int> o = ::ycv_gen_t()(x, 3);
    }
#endif

    {
        int const x = 3;
        our_type<int const, int> o = ::make_our_type(x, 3);
    }

    {
        int const x = 3;
        int y = 4;
        boost::tuples::get<2>( ::my_tie(1, x, y) ) = 10;
        BOOST_CHECK(y == 10);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
