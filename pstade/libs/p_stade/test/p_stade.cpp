

#include <pstade/vodka/drink.hpp>

#include <pstade/unit_test.hpp>


#include <boost/assert.hpp>


inline void bar() {}

inline void foo(bool b)
{
    if (b)
        bar();
}

void pstade_unit_test()
{
    ::foo(true);
}
