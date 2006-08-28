//#include <pstade/../libs/wine/test/contract.cpp>


#include <pstade/contract.hpp>


#include <cmath>
#include <pstade/is_same.hpp>


inline
float square_root(float x)
{
    PSTADE_PRECONDITION
    (
        (x >= 0)
    )
    PSTADE_POSTCONDITION(float)
    (
        ((result * result) == x)
    )

    PSTADE_RETURN(std::sqrt(x));
}


struct Date
{
    Date(int month, int day) :
        m_month(month), m_day(day)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION
        (
            (month != 999)
            (day != 999)
        )
    }

    ~Date()
    {
        PSTADE_DESTRUCTOR_PRECONDITION
        (~) // empty
    }

    void set_xmas()
    {
        PSTADE_PUBLIC_PRECONDITION
        (~)
        PSTADE_POSTCONDITION(void)
        (
            (m_month == 12)
            (m_day == 25)
        )

        m_month = 12;

        PSTADE_INVARIANT ( (m_month == 12) ) // block invariant

        m_day = 25;

        PSTADE_RETURN(void);
    }

    template< class T >
    T& set_day(T const& day)
    {
        PSTADE_POSTCONDITION(T&)
        (
            (result == day)
            (pstade::is_same(result, m_day))
        )

        if (m_day != day) {
            m_day = day;
            PSTADE_RETURN(m_day);
        }
        else {
            PSTADE_RETURN(m_day);
        }
    }

private:
    int m_month;
    int m_day;

    PSTADE_CLASS_INVARIANT
    (
        (1 <= m_month && m_month <= 12)
        (1 <= m_day && m_day <= 31)
    )
};


void test()
{
    float f = ::square_root(121);
    (void)f;

    Date d(4, 10);
    d.set_xmas();
    int a_day = d.set_day(25);
    PSTADE_INVARIANT ( (a_day == 25) )
    a_day = d.set_day(31);
    PSTADE_INVARIANT ( (a_day == 31) )
}


int main()
{
    ::test();
    return 0;
}
