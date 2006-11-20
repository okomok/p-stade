#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel.hpp>


#include <string>
#include <iostream>
#include <pstade/oven/functions.hpp>


void output(char ch)
{
    ::Sleep(std::rand()%100);
   std::cout << ch;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
        oven::parallel_for_each(rng, &output);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
