#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/dont_care.hpp>
#include <boost/test/minimal.hpp>


using namespace pstade;


struct to_any
{
    template<class To>
    operator To() const
    {
        return To(1,2);
    }
};


void foo(dont_care = 0, dont_care = 0)
{
}


void test()
{
    ::foo();
    ::foo(1);
    ::foo('a', 1.0);

#if 0 // ambiguous. no workaround.
    to_any a;
    ::foo(a);
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
