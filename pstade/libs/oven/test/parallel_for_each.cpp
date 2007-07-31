#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_for_each.hpp>
#include <boost/test/minimal.hpp>


#include <string>
#include <iostream>


void output(char ch)
{
    for (int i = 0; i < 1000000; ++i)
        ;

    // std::cout << ch;
    (void)ch;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
        oven::parallel_for_each(16, rng, &output);
    }
    {
        std::string b("0123401234");
        parallel_for_each(5, b, &output);
    }
    {
        std::string b;
        parallel_for_each(1, b, &output);
        parallel_for_each(100, b, &output);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
