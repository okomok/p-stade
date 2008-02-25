

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_all.hpp"
#include "./egg_all.hpp" // check include guards.


// #include "./egg_test.hpp"


#if defined(_CRT_SECURE_NO_DEPRECATE)
#error oops.
#endif
#if defined(_SCL_SECURE_NO_DEPRECATE)
#error oops.
#endif

#if defined(PSTADE_CRT_SECURE_NO_DEPRECATE)
#error oops.
#endif
#if defined(PSTADE_SCL_SECURE_NO_DEPRECATE)
#error oops.
#endif


using namespace boost::egg;


// warning check: This must be shown in IDE.
struct no_assignment
{
    int const &x;
};


int main()
{
    int x;
    no_assignment a = { x };

    return 0;
}
