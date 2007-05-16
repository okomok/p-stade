#include <pstade/unused.hpp>
// ...
virtual int test_unused(int x, int option)
{
    pstade::unused(option);
    return x+1;
}