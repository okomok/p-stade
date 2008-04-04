

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/indirect.hpp>
#include <boost/noncopyable.hpp>
#include <algorithm> // for_each


#include "./egg_example.hpp"


//[code_example_indirect
struct counter :
    private boost::noncopyable
{
    typedef void result_type;

    template<class T>
    void operator()(T const &)
    {
        m_count += 1;
    }

    int m_count;
    counter() : m_count(0) {}
};

void egg_example()
{
    counter c;
    int a[] = {1,2,3};
    std::for_each(a, a+3, indirect(&c)); /*< `indirect(&c)` is copyable, whereas `c` is not. >*/
    BOOST_CHECK(c.m_count == 3);
}
//]
