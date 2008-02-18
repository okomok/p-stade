

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/constructor.hpp>
#include "./egg_test.hpp"


#include <boost/egg/to_value.hpp>
#include <string>
#include <boost/egg/result_of.hpp>
#include <utility>


using boost::egg::result_of;
#include "./using_egg.hpp"


std::pair<int, char> foo()
{
    return constructor(3, 'c');
}


struct eater
{
    template<class T>
    explicit eater(T) { }

    eater(int i) { }

    eater() { }
};


void eat2()
{
    eater e_ = constructor();
}

void eat3(eater e  = constructor())
{
    (void)e;
}


#if !defined(__GNUC__)
// GCC3.4 and GCC4.1.2 prefers direct-initialization to copy-initialization
// in the case of default-argument. This must be bug of GCC.
// I don't know the exact condition; eater compiles. Why?
void buz(std::string s = constructor())
{
    (void)s;
}
#endif


void bar(std::pair<int, char> p = constructor(3, 'c'))
{
    BOOST_CHECK(p == std::make_pair(3, 'c'));
}


void egg_test()
{
    {
        result_of<X_construct<std::string>(char const*)>::type
            x = X_construct<std::string>()("hello"|to_value);
        BOOST_CHECK( x == std::string("hello") );
    }
    {
        std::string x = constructor("hello");
        BOOST_CHECK( x == std::string("hello") );
    }
    {
        std::string x = constructor();
    }
    {
        BOOST_CHECK(foo() == std::make_pair(3, 'c'));
    }
    {
        bar();
        bar(constructor(3, 'c'));
    }
    {
        eat2();
    }
    {
        eat3();
    }
#if !defined(__GNUC__)
    {
        buz();
    }
#endif
    {
        std::string s_ = constructor();
    }
}
