
#include <pstade/minimal_test.hpp>


int const g_ci = 12;
struct iklass
{
    iklass(int const &i)
    {
        BOOST_CHECK(&i == &g_ci);
    }
};


struct udt {};
udt const g_cu = {};

struct uklass
{
    uklass(udt const &u)
    {
        BOOST_CHECK(&u == &g_cu);
    }
};


void test()
{
    iklass ik = g_ci; // fails.
    uklass uk = g_cu; // ok.
}


void pstade_minimal_test()
{
    ::test();
}
