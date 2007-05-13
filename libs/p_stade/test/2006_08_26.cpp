#include <pstade/vodka/drink.hpp>


#include "./contract.hpp"


#include <cmath>
#include <iostream>


inline
float square_root(float x)
    PSTADE_PRECONDITION
    (
        assert(x >= 0);
    )
{
    PSTADE_RETURN( std::sqrt(x) );
}
    PSTADE_POSTCONDITION(float)
    (
        assert((*result * *result) == x);
    )


inline
void do_something(float x)
    PSTADE_PRECONDITION
    (
        assert(x == 0);
    )
{
    std::cout << x;
}
    PSTADE_POSTCONDITION(void)
    (
        ;
    )


void test()
{
    ::square_root(6400);
    ::do_something(10);

}


int main()
{
    ::test();
}
