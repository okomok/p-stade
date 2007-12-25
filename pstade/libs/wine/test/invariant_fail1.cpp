#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/invariant.hpp>
#include <pstade/minimal_test.hpp>


struct my_klass
{
    my_klass(int int1, int int2) : m_int1(int1), m_int2(int2)
    {
        //
        // initialize.
        //
        m_int1 = 999;


        PSTADE_INVARIANT_ASSERT();
    }

    void foo()
    {
        PSTADE_INVARIANT_SCOPE();

        //
        // do something.
        //
    }

    void bar()
    {
        // ASSERT and SCOPE can work together.
        PSTADE_INVARIANT_ASSERT();
        PSTADE_INVARIANT_SCOPE();
    }

    ~my_klass()
    {
        PSTADE_INVARIANT_ASSERT();

        //
        // clean up.
        //
        m_int1 = m_int2 = 0;
    }

private:
    PSTADE_INVARIANT
    (
        (m_int1 == 10)
        (m_int2 == 11)
    )

    int m_int1, m_int2;
};


void pstade_minimal_test()
{
    my_klass k(10, 11);
    k.foo();
    k.bar();
}
