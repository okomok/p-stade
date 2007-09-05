#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/sig_template.hpp>
#include <pstade/minimal_test.hpp>


struct my_bindable
{
#include PSTADE_EGG_SIG_TEMPLATE()
};


struct my_bindable2
{
#include PSTADE_EGG_SIG_TEMPLATE()
};


void pstade_minimal_test()
{
    std::string s1, s2("hello");
}
