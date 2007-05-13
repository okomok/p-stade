

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <string>
#include <boost/utility/enable_if.hpp>
#include <iostream>


template<class X>
struct tag { typedef void type; };

template<class X>
struct tag_aux : tag<typename boost::remove_cv<X>::type> {};

template<class X, class EnableIf = void>
struct hello_base;

template<class X, class Tag = typename tag_aux<X>::type>
struct hello : hello_base<X, void> {};


// type layer

struct my {};

template<>
struct hello<my>
{
    static void say()
    {
        std::cout << "hello, my type\n";
    }
};


// tag layer

struct string_tag;

template<>
struct tag<std::string>
{
    typedef string_tag type;
};

template<>
struct tag<std::wstring>
{
    typedef string_tag type;
};

template<class X>
struct hello<X, string_tag>
{
    static void say()
    {
        std::cout << "hello, string\n";
    }
};


// enable_if layer

template<class X>
struct hello_base<X, typename boost::enable_if< boost::is_integral<X> >::type>
{
    static void say()
    {
        std::cout << "hello, integer\n";
    }
};


int main()
{
    hello<my>::say();
    hello<std::string>::say();
    hello<int>::say();
}


