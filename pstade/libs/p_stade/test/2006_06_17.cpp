#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/detail/callable.hpp>


#include <iostream>
#include <string>
#include <pstade/instance.hpp>
#include <pstade/unused.hpp>


struct fun_t :
    boost::detail::callable<fun_t>
{
    template< class F >
    struct apply;

    template< class F, class A0, class A1, class A2 >
    struct apply<F(A0, A1, A2)>
    {
        typedef std::string type;
    };

    template< class A0, class A1, class A2 >
    std::string call(A0& a0, A1& a1, A2& a2) const
    {
        pstade::unused(a0, a1, a2);
        return "goodbye, forwarding problem";
    }
};


PSTADE_INSTANCE(fun_t const, fun, value)


void test()
{
    int x, y, z;
    std::cout << fun(1, 2, 3);

    std::cout << fun(x, 2, 3);

    std::cout << fun(1, y, 3);

    std::cout << fun(1, 2, z);
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}

