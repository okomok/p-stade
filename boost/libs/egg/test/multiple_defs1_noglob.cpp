

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_all.hpp"
#include "./egg_all.hpp" // check include guards.


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


int check_include_guard()
{
    using namespace boost::egg;
    using function;
    using function_facade;
    using generator;
    using implicit;
    using poly;
    using static_;
    using variadic;
    using ambi1;
    using compose;
    using curry2;
    using uncurry;
    using fix;
    using flip;
    using fuse;
    using unfuse;
    using indirect;
    using lazy;
    using memoize;
    using mono;
    using perfect;
    using pipable;
    using regular;
    using return_;
    using tagged;
    using adapted_to;
    using always;
    using identity;
    using apply;
    using bll_bind;
    using bll_1;
    using X_construct;
    using X_construct_braced1;
    using X_construct_braced2;
    using X_construct_variadic1;
    using get;
    using pack;
    using result_of_;
    #if !defined(BOOST_EGG_CONST)
        #error oops.
    #endif
    using apply_little;
    using call_little;
    #if !defined(BOOST_EGG_DEDUCED_CONST)
        #error oops.
    #endif
}


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
