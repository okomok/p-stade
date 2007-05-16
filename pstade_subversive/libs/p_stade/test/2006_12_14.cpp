#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <utility>
#include <pstade/unparenthesize.hpp>


#define FOO(T, V, f, s) T V(f, s);

#define BAR(T, V, f, s) PSTADE_UNPARENTHESIZE(T) V(f, s);


void test()
{
    FOO(const PSTADE_UNPARENTHESIZE((std::pair<int,int>)), p1, 1, 2)
    BAR((std::pair<int,int>) const, p2, 1, 2)

    BOOST_CHECK(p1 == p2);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
