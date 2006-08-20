#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/invariant.hpp>


#include <iostream>
#include <boost/assert.hpp>


using namespace pstade;


struct A
{
    void foo()
    {
        invariant holds(*this);
        
        // do something
    }

private:

    friend class invariant::access;

    bool pstade_invariant()
    {
        std::cout << "A holds\n";
        return true;
    }
};


struct B : A
{
    void bar()
    {
        invariant holds(*this);
        
        // do something
    }

private:

    friend class invariant::access;

    bool pstade_invariant()
    {
        std::cout << "B holds\n";
        return invariant::holds<A>(*this) && true;
    }
};


void test()
{
    A a;
    a.foo();
    (void)a;

    B b;
    b.bar();
    (void)b;
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
