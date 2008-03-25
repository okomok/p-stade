

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


template<class T>
struct extract
{
    // T m_y; // error: needs complete
    typedef typename T::foo type;
};

struct bar
{
    typedef int foo;
    extract<bar>::type m_x;
};


int main()
{
    bar b;
    (void)b;
}
