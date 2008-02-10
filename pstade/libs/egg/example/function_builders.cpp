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
#include <pstade/egg/implicit.hpp>
#include <pstade/egg/polymorphic.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/egg/static.hpp>
#include <pstade/egg/apply.hpp>


#include <boost/array.hpp>
#include <pstade/egg/construct_braced2.hpp>
#include <boost/lexical_cast.hpp>
#include <utility> //pair
#include <string>
#include <vector>
#include <boost/mpl/always.hpp>
#include <boost/ref.hpp>


using pstade::result_of;
using namespace pstade::egg;


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
PSTADE_POD_CONSTANT((T_unwrap), unwrap) = {{}};

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
}; /*<< `plus_to<>` is already a MajorFunctionObject type. >>*/

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

T_lexical const lexical = PSTADE_EGG_IMPLICIT();

void test_automatic()
{
    std::string str = lexical(20);
    BOOST_CHECK( str == "20" );
}
//]


//[code_polymorphic_example
struct my_begin_impl
{
    template<class Seq>
    struct apply
    {
        typedef apply type;
        typedef typename Seq::iterator result_type;

        result_type operator()(Seq &seq) const
        {
            return seq.begin();
        }
    };

    template<class Seq>
    struct apply<Seq const>
    {
        typedef apply type;
        typedef typename Seq::const_iterator result_type;

        result_type operator()(Seq const &seq) const
        {
            return seq.begin();
        }
    };
};

typedef polymorphic<my_begin_impl>::type T_my_begin;
T_my_begin const my_begin = PSTADE_EGG_POLYMORPHIC();

template<class X>
struct mono_my_identity
{
    typedef X &result_type;

    result_type operator()(X &x) const
    {
        return x;
    }
};

typedef
    /*<< When function is not overloaded with different arities,
         you can use __MPL_PLACEHOLDER_EXPRESSION__. >>*/
    polymorphic< mono_my_identity<boost::mpl::_1> >::type
T_my_identity;

T_my_identity const my_identity = PSTADE_EGG_POLYMORPHIC();

void test_polymorphic()
{
    std::string str("abc");
    std::string const cstr("ayz");
    result_of<T_my_begin(result_of<T_my_identity(std::string &)>::type)>::type
        i = my_begin(my_identity(str));
    BOOST_CHECK( *i == *my_begin(cstr) );
}
//]



//[code_static_example
typedef static_<X_apply<boost::mpl::_1>, by_value>::type T_apply_by_value;
T_apply_by_value const apply_by_value = PSTADE_EGG_STATIC();
//]


//[code_generator_example
typedef
    generator<
        std::pair< deduce<boost::mpl::_1, as_value>, deduce<boost::mpl::_2, as_value> >
    >::type
T_make_pair;

T_make_pair const make_pair = PSTADE_EGG_GENERATOR();

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

T_make_array4 const make_array4 = PSTADE_EGG_GENERATOR();

void test_generator()
{
    BOOST_CHECK( make_pair(10, std::string("generator"))
        == std::make_pair(10, std::string("generator")) );

    boost::array<int, 4> arr = {{1,2,3,4}};
    BOOST_CHECK( make_array4(1,2,3,4) == arr );
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
    test_polymorphic();
    test_generator();
}
