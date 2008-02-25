

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


void check_include_guards()
{
    using namespace boost;

    using egg::by_perfect;
    using egg::by_ref;
    using egg::by_cref;
    using egg::by_value;
    #if !defined(BOOST_EGG_FUNCTION_PREAMBLE)
        #error oops.
    #endif
    using egg::apply_little;
    using egg::call_little;
    #if !defined(BOOST_EGG_DEDUCED_CONST)
        #error oops.
    #endif

    using egg::function;
    using egg::function_facade;
    using egg::generator;
    using egg::implicit;
    using egg::poly;
    using egg::static_;
    using egg::variadic;
    using egg::ambi1;
    using egg::compose;
    using egg::curry2;
    using egg::uncurry;
    using egg::fix;
    using egg::flip;
    using egg::fuse;
    using egg::unfuse;
    using egg::indirect;
    using egg::lazy;
    using egg::memoize;
    using egg::mono;
    using egg::perfect;
    using egg::pipable;
    using egg::regular;
    using egg::return_;
    using egg::tagged;
    using egg::adapted_to;
    using egg::always;
    using egg::identity;
    using egg::apply;
    using egg::bll_bind;
    using egg::bll_1;
    using egg::X_construct;
    using egg::X_construct_braced1;
    using egg::X_construct_braced2;
    using egg::X_construct_variadic1;
    using egg::get;
    using egg::pack;

    using egg::expr;
    using namespace egg::infix;
    using namespace boost::lambda_result_of_detail;

    using egg::result_of_;
    using egg::details::has_use_deduced_form;
    #if !defined(BOOST_EGG_CONST)
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
