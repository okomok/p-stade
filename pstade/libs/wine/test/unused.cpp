#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused.hpp>
#include <boost/test/minimal.hpp>


struct to_any
{
    template<class To>
    operator To() const
    {
        return To(1,2);
    }
};

void test()
{
    pstade::unused();
    pstade::unused(0,1,2,3,4,5,6,7,8);

    to_any a;
    pstade::unused(a, to_any());
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
