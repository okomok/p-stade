#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/sausage.hpp>


#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>


struct my_routine
{
    typedef int routine_result_type;

    template< class Yield >
    int operator()(Yield yield)
    {
        int min = 0, max = 30;
        for (int i = min; i < max; ++i)
            yield(min++);

        return min;
    }
};


void test()
{
    using namespace pstade;
    using namespace boost;
    using namespace sausage;

    BOOST_FOREACH (int i, ::my_routine()|yielded) {
        std::cout << i;
        if (i == 15)
            break;
    }
};


int test_main(int, char*[])
{
    ::test();
    return 0;
}
