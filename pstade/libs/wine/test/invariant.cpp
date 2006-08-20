#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/invariant.hpp>


struct A
{
    void foo()
    {
        pstade::invariant holds(*this);
    }

private:

    friend class pstade::invariant::access;

    bool pstade_invariant()
    {
        return true;
    }
};


void test()
{
    A a;
    a.foo();
    (void)a;
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
