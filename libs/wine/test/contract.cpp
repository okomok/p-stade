#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/contract.hpp>
#include <pstade/unit_test.hpp>


#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_integral.hpp>


using namespace pstade;


template< class T >
void bar(T i)
{
    T oldof_i = i;

    PSTADE_PRECONDITION (
        (i > 0)
        (i != 999)
    )
    PSTADE_POSTCONDITION(void) (
        (i == oldof_i + 1)
    )

    ++i;
    PSTADE_RETURN(void);
}


inline
float square_root(float x)
{
    PSTADE_POSTCONDITION(float) (
        ((result * result) == x)
    )

    PSTADE_RETURN(std::sqrt(x));
}

template< class T >
T identity_func(T x)
{
    PSTADE_POSTCONDITION(T) (
        (result == x)
    )

    PSTADE_RETURN(x);
}


struct date
{
    date(int day, int hour) :
        m_day(day), m_hour(hour)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (
            empty
        )
    }

    void set_day(int day)
    {
        PSTADE_PUBLIC_PRECONDITION (
            (1 <= day && day <= 31)
        )

        m_day = day;
    }

private:
    PSTADE_CLASS_INVARIANT
    (
        (1 <= m_day && m_day <= 31)
        (0 <= m_hour && m_hour < 24)
    )

    int m_day, m_hour;
};


template< class T >
struct A
{
private:
    PSTADE_CLASS_INVARIANT
    (
        empty // BOOST_MPL_ASSERT((boost::is_integral<T>)); // bad style?
    )
};


struct B : A<int>
{
    B(int f, int l) :
        m_f(f)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (
            (f <= l)
        )

        // set up here
        m_l = l;
    }

    ~B()
    {
        PSTADE_DESTRUCTOR_PRECONDITION (
            empty
        )

        // clean up here

        m_f = 500; // violate it here, but ok.
    }
    
    void set_f(int f)
    {
        PSTADE_PUBLIC_PRECONDITION (
            (f == 9898 || f <= m_l)
        )

        m_f = f;
    }

    void barbar()
    {
        PSTADE_PUBLIC_PRECONDITION (
            empty
        )
    }

    void foofoo(int i)

    {
        PSTADE_PRECONDITION (
            (i == 10)
        )

        m_f = i;
    }

private:
    int m_f, m_l;

    PSTADE_CLASS_INVARIANT
    (
        (pstade::invariant< A<int> >(*this)) // you should call
        ((std::map<int,int>().empty()))
        (m_f != 500)
        (m_f != 10492 || m_l != 999)
    )
};


std::stringstream g_ss;

struct test_man
{
    test_man()
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (
            (g_ss << "_pc_")
        )

        g_ss << "_bc_";
    }

    ~test_man()
    {
        PSTADE_DESTRUCTOR_PRECONDITION (
            (g_ss << "_pd_")
        )

        g_ss << "_bd_";
    }

    void do_it1()
    {
        PSTADE_PUBLIC_PRECONDITION (
            (g_ss << "_p1_")
        )

        g_ss << "_b1_";
    }

    void do_it2()
    {
        PSTADE_PRECONDITION (
            (g_ss << "_p2_")
        )

        g_ss << "_b2_";
    }

private:
    PSTADE_CLASS_INVARIANT
    (
        (g_ss << "_I_")
    )
};

//
//

int g_x;

int& g_test1()
{
    PSTADE_POSTCONDITION(int&)
    (
        (result == 4)
    )

    g_x = 4;
    PSTADE_RETURN(g_x);
}


int g_test2(int i)
{
    PSTADE_POSTCONDITION(int)
    (
        (i == 4)
        (result == 4)
    )

    if (i == 3) {
        ++i;
        PSTADE_RETURN(i);
    }
    else
        PSTADE_RETURN(4);
}

void g_test3()
{
    PSTADE_POSTCONDITION(void)
    (
        (g_x == 5)
    )

    ++g_x;
    PSTADE_RETURN(void);
}


int const g_cx(3);

int const& g_test4()
{
    PSTADE_POSTCONDITION(int const&)
    (
        (g_cx == 3)
    )

    PSTADE_RETURN(g_cx);
}

void pstade_unit_test()
{
    ::g_test1();
    ::g_test2(4);
    ::g_test3();
    ::g_test4();

    ::bar(9);
    ::identity_func(10);
    
    B b(80, 5000);
    b.set_f(80);
    
    for (int i = 0;;) {
        PSTADE_INVARIANT ( (i < 10) )

        if (++i == 10)
            break;
    }

    (void)b;

    ::square_root(6400);

    ::date d(30, 13);

#if !defined(NDEBUG)
    {
        std::cout << "test_man test\n";
        ::test_man man;
        BOOST_CHECK( g_ss.str() == "_pc__bc__I_" );
        g_ss.str("");
        man.do_it1();
        BOOST_CHECK( g_ss.str() == "_p1__I__b1__I_" );
        g_ss.str("");
        man.do_it2();
        BOOST_CHECK( g_ss.str() == "_p2__b2_" );
        g_ss.str("");
    }
    BOOST_CHECK( g_ss.str() == "_pd__I__bd_" );
#endif

    PSTADE_INVARIANT (-)
    PSTADE_INVARIANT (+)

}
