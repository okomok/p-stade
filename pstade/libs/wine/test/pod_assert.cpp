#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_assert.hpp>
#include <pstade/lightweight_test.hpp>


struct udt { int a; char b; };


PSTADE_POD_ASSERT((int));
PSTADE_POD_ASSERT((udt));


PSTADE_POD_ASSERT_OF((int), x);
PSTADE_POD_ASSERT_OF((udt), y);


template<class T>
void test_tpl()
{
    PSTADE_POD_ASSERT((T));
    PSTADE_POD_ASSERT_OF((T), x);
};


void pstade_lightweight_test()
{
    test_tpl<int>();
}
