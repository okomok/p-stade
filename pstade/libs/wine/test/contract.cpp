#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/contract.hpp>


#include <cmath>
#include <iostream>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_integral.hpp>


using namespace pstade;


template< class T >
void bar(T i)
    PSTADE_PRECONDITION_
    (
        if (i == 100)
            assert(i < 200);
    )
{
    ++i;

    PSTADE_BLOCK_INVARIANT (
        if (i != 200)
            assert(i != 200);
    )
}


inline
float square_root(float x)
    PSTADE_PRECONDITION (
        assert(x >= 0);
    )
{
    float result = std::sqrt(x);

    PSTADE_BLOCK_INVARIANT (
        assert((result * result) == x);
    )

    return result;
}


struct date
{
    date(int day, int hour) :
        m_day(day), m_hour(hour)
    {
    }

    void set_day(int day)
        PSTADE_PUBLIC_PRECONDITION (
            assert(1 <= day && day <= 31);
        )
    {
        m_day = day;
    }

private:
    PSTADE_INVARIANT
    {
	    assert(1 <= m_day && m_day <= 31);
	    assert(0 <= m_hour && m_hour < 24);
    }

    int m_day, m_hour;
};


template< class T >
struct A
{
private:

    PSTADE_INVARIANT
    {
        BOOST_MPL_ASSERT((boost::is_integral<T>)); // bad style?
    }
};


struct B : A<int>
{
    B(int f, int l) :
        m_f(f), m_l(l)
    {
        PSTADE_BLOCK_INVARIANT (
            assert(f <= l);
        )

        // set up here

        PSTADE_ASSERT_INVARIANT;
    }

    ~B()
    {
        PSTADE_ASSERT_INVARIANT;

        // clean up here
    }
    
    void set_f(int f)
        PSTADE_PUBLIC_PRECONDITION
        (
            if (f != 9898)
                assert(f <= m_l);
        )
    {
        m_f = f;
    }

    void barbar()
        PSTADE_PUBLIC_PRECONDITION
        (
            ;
        )
    {

    }

    void foofoo(int i)
        PSTADE_PRECONDITION
        (
            assert(i == 10);
        )
    {
        m_f = i;
    }

private:
    int m_f, m_l;

    PSTADE_INVARIANT
    {
        assert_invariant< A<int> >(*this);
        assert(m_f != 500);
        if (m_f == 10492)
            assert(m_l != 999);
    }
};


void test()
{
    ::bar(9);
    
    B b(80, 5000);
    b.set_f(80);
    
    for (int i = 0;;) {
        PSTADE_BLOCK_INVARIANT ( assert(i < 10); )

        if (++i == 10)
            break;
    }

    (void)b;

    ::square_root(6400);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
