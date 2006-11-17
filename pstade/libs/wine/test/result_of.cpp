#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>


template< class T >
struct chat_monchy_
{
    template< class Sig >
    struct result;

    template< class F, class Array >
    struct result<F(Array&)>
    {
        typedef int type;
    };

    template< class Array >
    int operator()(Array&)
    {
        return 0;
    };

    template< class Array >
    int operator()(Array const&)
    {
        return 0;
    };
};


template< class T >
struct chat_monchy : chat_monchy_<T> { };


void test()
{

    {
        int array[] = { 1,2,3 };
        boost::result_of<chat_monchy<int>(int (&)[3])>::type result
            = ::chat_monchy<int>()(array);
    }

    {
        int const array[] = { 1,2,3 };
        boost::result_of<chat_monchy<int>(int const (&)[3])>::type result
            = ::chat_monchy<int>()(array);
    }

    {
        int i = 10;
        boost::result_of<chat_monchy<int>(int&)>::type result
            = ::chat_monchy<int>()(i);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
