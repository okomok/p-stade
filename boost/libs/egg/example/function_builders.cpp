

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../test/egg_test.hpp"


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/function_facade.hpp>
#include <boost/egg/implicit.hpp>
#include <boost/egg/poly.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/apply.hpp>


#include <boost/array.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/lexical_cast.hpp>
#include <utility> //pair
#include <string>
#include <vector>
#include <boost/mpl/always.hpp>
#include <boost/ref.hpp>


using boost::egg::result_of_;
using namespace boost::egg;


//[code_function_example
struct little_unwrap
{
    template<class Me, class A>
    struct apply
    {
        /*<< `A` is possibly cv-qualifed but not reference type. >>*/
        typedef A &type;
    };

    template<class Me, class T>
    struct apply< Me, boost::reference_wrapper<T> >
    {
        typedef T &type;
    };

    template<class Me, class T>
    struct apply< Me, boost::reference_wrapper<T> const >
    {
        typedef T &type;
    };

    template<class Re, class A>
    /*<< `Re` is `apply<little_unwrap const, A>::type`. >>*/
    Re call(A &a) const
    {
        return a;
    }
};

typedef function<little_unwrap> T_unwrap;
T_unwrap const unwrap = {{}};

void test_function()
{
    int i = 1;
    BOOST_CHECK( &(unwrap(i)) == &i );
    BOOST_CHECK( &(unwrap(boost::ref(i))) == &i );
}
//]



//[code_function_by_value_example
struct little_value_identity
{
    template<class Me, class A>
    struct apply
    {
        /*<< `A` is a "plain" type. >>*/
        typedef A type;
    };

    template<class Re, class A>
    /*<< `Re` is `A`. >>*/
    Re call(A a) const
    {
        return a;
    }
};

typedef function<little_value_identity, by_value> T_value_identity;
T_value_identity const value_identity = {{}};

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
    template<class Me, class A>
    struct apply
    {
        typedef T type;
    };

    template<class Re, class A>
    Re call(A &a) const
    {
        return m_x + a;
    }

    explicit plus_to(T x)
        : m_x(x)
    {}

private:
    T m_x;
};
/*< `plus_to<>` is already a MajorFunctionObject type. >*/
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


//[code_implicit_example
template<class To>
struct X_lexical_cast
{
    typedef To result_type;

    template<class From>
    To operator()(From from) const
    {
        return boost::lexical_cast<To>(from);
    }
};

typedef
    implicit< X_lexical_cast<boost::mpl::_> >::type
T_lexical;

T_lexical const lexical = BOOST_EGG_IMPLICIT();

void test_automatic()
{
    std::string str = lexical(20);
    BOOST_CHECK( str == "20" );
}
//]


//[code_poly_example
template<class F, class X>
struct mono_twice
{
    typedef typename
        result_of_<F(typename result_of_<F(X &)>::type)>::type
    result_type;

    result_type operator()(F &f, X &x) const
    {
        return f(f(x));
    }
};

typedef
    poly< mono_twice<boost::mpl::_, boost::mpl::_> >::type
T_twice;

T_twice const twice = BOOST_EGG_POLY();

int increment(int i) { return i+1; }

void test_poly()
{
    BOOST_CHECK(twice(&increment, 3) == 1+1+3);
}
//]



//[code_static_example
typedef static_<X_apply<boost::mpl::_1>, by_value>::type T_apply_by_value;
T_apply_by_value const apply_by_value = BOOST_EGG_STATIC();
//]


//[code_generator_example
typedef
    generator<
        std::pair< deduce<boost::mpl::_1, as_value>, deduce<boost::mpl::_2, as_value> >
    >::type
T_make_pair;

T_make_pair const make_pair = BOOST_EGG_GENERATOR();

struct array_int4 :
    boost::mpl::always< boost::array<int, 4> >
{ };

typedef
    generator<
        array_int4,
        boost::use_default,
        /*<< `X_construct_braced1` too is ok. gcc-4.1 warns about fewer braces, though. >>*/
        X_construct_braced2<>
    >::type
T_make_array4;

T_make_array4 const make_array4 = BOOST_EGG_GENERATOR();

void test_generator()
{
    BOOST_CHECK( make_pair(10, std::string("generator"))
        == std::make_pair(10, std::string("generator")) );

    boost::array<int, 4> arr = {{1,2,3,4}};
    BOOST_CHECK( make_array4(1,2,3,4) == arr );
}
//]


void egg_test()
{
    test_function();
    test_function_by_value();
    test_function_facade();
#if 0
    test_envelope();
#endif
    test_automatic();
    test_poly();
    test_generator();
}
