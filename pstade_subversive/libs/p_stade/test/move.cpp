// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define DEBUG_MOVE
#include <boost/move.hpp>
#include <boost/static_assert.hpp>
#include "say.hpp"
#include "x.hpp"

//
// Some functions we can use to test the passing of Xs in and out of
// functions.
//
X source()
{
    return X();
}

X const csource()
{
    return X();
}

void sink(X)
{
    SAY("in rvalue sink");
}

void sink2(X&)
{
    SAY("in non-const lvalue sink2");
}

void sink2(X const&)
{
    SAY("in const lvalue sink2");
}

void sink3(X&)
{
    SAY("in non-const lvalue sink3");
}

template <class T>
void tsink(T)
{
    SAY("in templated rvalue sink");
}

int main()
{
    SAY(" ------ test 1, direct init from rvalue ------- ");
    X::expect_move();
    X z2(source());

    SAY(" ------ test 2, copy init from rvalue ------- ");
    X::expect_move();
    X z4 = X();

    SAY(" ------ test 3, copy init from lvalue ------- ");
    X::expect_copy();
    X z5 = z4;

    SAY(" ------ test 4, direct init from lvalue ------- ");
    X::expect_copy();
    X z6(z4);

    SAY(" ------ test 5, construct const ------- ");
    X const z7;

    SAY(" ------ test 6, copy init from lvalue ------- ");
    X::expect_copy();
    X z8 = z7;

    SAY(" ------ test 7, direct init from lvalue ------- ");
    X::expect_copy();
    X z9(z7);

    SAY(" ------ test 8, pass rvalue by-value ------- ");
    X::expect_move();
    sink(source());

    SAY(" ------ test 9, pass const rvalue by-value ------- ");
    X::expect_move();
    sink(csource());

    SAY(" ------ test 10, pass rvalue by overloaded reference ------- ");
    X::expect_move();
    sink2(source());

    SAY(" ------ test 11, pass const rvalue by overloaded reference ------- ");
    X::expect_move();
    sink2(csource());

    SAY(" ------ test 13, pass lvalue by-value ------- ");
    X::expect_copy();
    sink(z5);

    SAY(" ------ test 14, pass const lvalue by-value ------- ");
    X::expect_copy();
    sink(z7);

    SAY(" ------ test 15, pass lvalue by-reference ------- ");
    X::expect_copy();
    sink2(z4);

    SAY(" ------ test 16, pass const lvalue by const reference ------- ");
    X::expect_copy();
    sink2(z7);

    SAY(" ------ test 17, pass rvalue by value to template param ------- ");
    X::expect_move();
    tsink(source());

    SAY(" ------ test 18, direct initialize a const X with an X ------- ");
    X::expect_move();
    typedef X const XC;
    sink2(XC(X()));

    SAY(" ------ test 19, assign from non-const lvalue ------- ");
    X::expect_copy();
    z4 = z5;

    SAY(" ------ test 20, assign from const lvalue ------- ");
    X::expect_copy();
    z4 = z7;

    SAY(" ------ test 21, assign from rvalue ------- ");
    X::expect_move();
    z4 = source();

    SAY(" ------ test 22, explicit move direct init from movable lvalue ------- ");
    BOOST_STATIC_ASSERT(boost::is_movable<X>::value);
    X::expect_move();
    X z10(boost::move(z2));
    
    SAY(" ------ test 23, explicit move copy init from movable lvalue ------- ");
    X::expect_move();
    X z11 = boost::move(z9);
    
    SAY(" ------ test 24, move assign from movable lvalue ------- ");
    X::expect_move();
    z10 = boost::move(z8);
    
    SAY(" ------ test 25, request move construct from non-movable lvalue ------- ");
    BOOST_STATIC_ASSERT(!boost::is_movable<std::string>::value);
    std::string s1("hello");
    std::string s2(boost::move(s1));

    SAY("----- done, with " << X::suboptimal_copies << " suboptimal copies -----");
    return 0;
}
