#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <pstade/egg/function.hpp>
#include <pstade/egg/function_by_value.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/envelope.hpp>


#include <vector>


using namespace pstade::egg;


//[code_function_example
struct baby_second_argument
{
    template<class Myself, class A1, class A2>
    struct apply
    {
        /*<< Don't forget add reference. >>*/
        typedef A2 &type;
    };

    /*<< `Result` is `A2 &`. >>*/
    template<class Result, class A1, class A2>
    Result call(A1 &a1, A2 &a2) const
    {
        return a2;
    }
};

typedef function<baby_second_argument> op_second_argument;
op_second_argument const second_argument = {{}}; /*< A braced initialization is ok, because `op_second_argument` is /POD/. >*/

void test_function()
{
    int i = 2;
    BOOST_CHECK( &(second_argument(1, i)) == &i );
    BOOST_CHECK( second_argument(1, i) == 2 );
}
//]



//[code_function_by_value_example
struct baby_value_identity
{
    template<class Myself, class A>
    struct apply
    {
        /*<< `A` is a "plain" type. >>*/
        typedef A type;
    };

    /*<< `Result` is `A`. >>*/
    template<class Result, class A>
    Result call(A a) const
    {
        return a;
    }
};

typedef function_by_value<baby_value_identity> op_value_identity;
op_value_identity const value_identity = {{}};

void test_function_by_value()
{
    BOOST_CHECK( value_identity(1) == 1 );
}
//]



//[code_function_facade_example
template<class T>
struct plus_to
    : function_facade< plus_to<T> >
{
    template<class Myself, class A>
    struct apply
    {
        typedef T type;
    };

    template<class Result, class A>
    Result call(A& a) const
    {
        return m_x + a;
    }

    explicit plus_to(T x)
        : m_x(x)
    {}

private:
    T m_x;
};

/*<< `plus_to<>` is already a full-fledged function. >>*/

template<class T>
plus_to<T> make_plus_to(T x)
{
    return plus_to<T>(x);
}

void test_function_facade()
{
    BOOST_CHECK( make_plus_to(1)(3) == 4 );
}
//]


//[code_envelope_example
struct baby_size
{
    template<class Myself, class X>
    struct apply
    {
        typedef std::size_t type;
    };

    template<class Result, class X>
    Result call(X &x) const
    {
        /*<< Call without explicit template arguments. >>*/
        return call_aux(x, envelope<Result>());
    }

    template<class Result, class Container>
    Result call_aux(Container& c, envelope<Result>) const
    {
        return c.size();
    }

    /*<< Overload for array reference. >>*/
    template<class Result, class T, std::size_t sz>
    Result call_aux(T (&a)[sz], envelope<Result>) const
    {
        return sz;
    }
};
//]

typedef function<baby_size> op_size;
op_size const size = {{}};

void test_envelope()
{
    std::vector<int> v(12);
    BOOST_CHECK( size(v) == 12 );
    int a[12];
    BOOST_CHECK( size(a) == 12 );
}


void pstade_minimal_test()
{
    test_function();
    test_function_by_value();
    test_function_facade();
    test_envelope();
}
