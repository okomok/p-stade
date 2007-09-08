#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <pstade/egg/by_perfect.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/automatic.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/egg/generator.hpp>


#include <boost/lexical_cast.hpp>
#include <utility> //pair
#include <string>
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

typedef function<baby_second_argument, by_perfect> op_second_argument;
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

typedef function<baby_value_identity, by_value> op_value_identity;
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
    Result call(A &a) const
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


//[code_automatic_example
template<class To>
struct xp_lexical_cast
{
    typedef To result_type;

    template<class From>
    To operator()(From from) const
    {
        return boost::lexical_cast<To>(from);
    }
};

typedef
    automatic< xp_lexical_cast<boost::mpl::_> >::type
op_lexicalize;

op_lexicalize const lexicalize = PSTADE_EGG_AUTOMATIC;

void test_automatic()
{
    std::string str = lexicalize(20);
    BOOST_CHECK( str == "20" );
}
//]


//[code_deferred_example
template<class X>
struct base_my_identity
{
    typedef X &result_type;

    result_type operator()(X &x) const
    {
        return x;
    }
};

typedef
    deferred< base_my_identity<boost::mpl::_1> >::type
op_my_identity;

op_my_identity const my_identity = PSTADE_EGG_DEFERRED;
//]

void test_deferred()
{
    int i = 10;
    BOOST_CHECK( &(my_identity(i)) == &i );
    BOOST_CHECK( my_identity(10) == 10 );
}


//[code_generator_example
typedef
    generator<
        std::pair< deduce<boost::mpl::_1, as_value>, deduce<boost::mpl::_2, as_value> >
    >::type
op_make_pair;

op_make_pair const make_pair = PSTADE_EGG_GENERATOR;

void test_generator()
{
    BOOST_CHECK( make_pair(10, std::string("generator"))
        == std::make_pair(10, std::string("generator")) );
}
//]


void pstade_minimal_test()
{
    test_function();
    test_function_by_value();
    test_function_facade();
#if 0
    test_envelope();
#endif
    test_automatic();
    test_deferred();
    test_generator();
}
