#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>


struct A
{
    typedef char char_type;
};

struct B : A
{
    char get_string()
    {
        return 'B';
    }
};

struct C : A
{
    char get_string()
    {
        return 'C';
    }
};


template< class T >
struct which :
    boost::enable_if<T>
{ };


template< class T, class = void >
struct customization;


template< >
struct customization<int>
{
    template< class Int >
    struct foo_result
    {
        typedef std::string type;
    };

    template< class Result >
    Result foo(int i)
    {
        return boost::lexical_cast<Result>(i);
    }
};


template< class T >
struct customization<T, typename which< boost::is_base_of< ::A, T > >::type>
{
    template< class A_ >
    struct foo_result
    {
        typedef typename A_::char_type type;
    };

    template< class Result, class A_ >
    Result foo(A_& a)
    {
        return a.get_string();
    }
};


template< class T >
typename ::customization<T>::template foo_result<T>::type
foo(T& x)
{
    typedef typename ::customization<T>::template foo_result<T>::type result_t;
    return ::customization<T>().template foo<result_t>(x);
}


void test()
{
    int i = 30;
    BOOST_CHECK( ::foo(i) == "30" );

    ::B b;
    ::C c;
    BOOST_CHECK( ::foo(b) == 'B' );
    BOOST_CHECK( ::foo(c) == 'C' );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
