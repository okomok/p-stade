#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/in_block.hpp>
#include <pstade/unit_test.hpp>
#include <boost/foreach.hpp>
#include "./detail/test.hpp"

#include <iostream>


namespace oven = pstade::oven;
using namespace oven;


struct my_block1
{
    typedef int yield_type;

    template< class Yield >
    void operator()(Yield yield) const
    {
        for (int i = 0; i < 500; ++i) {
            if (i == 10)
                yield.break_();
            else
                yield.return_(i);
        }
    }
};


struct my_block2
{
    typedef int yield_type;

    my_block2(int c) : m_c(c) { }

    int m_c;

    template< class Yield >
    void operator()(Yield yield) const
    {
        for (int i = 0; i < m_c; ++i) {
            yield(1);
            yield(2);
            yield.return_(3);
        }
    }
};


struct empty_block1
{
    typedef int yield_type;

    template< class Yield >
    void operator()(Yield ) const
    {

    }
};

struct empty_block2
{
    typedef int yield_type;

    template< class Yield >
    void operator()(Yield yield) const
    {
        yield.break_();
        yield(1);
    }
};



int g_int1 = 1, g_int2 = 2, g_int3 = 3;

struct reference_block
{
    typedef int& yield_type;

    template< class Yield >
    void operator()(Yield yield) const
    {
        yield(g_int1);
        yield(g_int2);
        yield(g_int3);
    }
};


int const g_cint1 = 1, g_cint2 = 2, g_cint3 = 3;

struct const_reference_block
{
    typedef int const& yield_type;

    template< class Yield >
    void operator()(Yield yield) const
    {
        yield(g_cint1);
        yield(g_cint2);
        yield(g_cint3);
    }
};


void pstade_unit_test()
{
    std::cout << "test begins..." << std::endl;

    try
    {
        for (int i = 0; i < 500; ++i) {
            {
                int a[] = { 0,1,2,3,4,5,6,7,8,9 };
                test::single_pass_readable(in_block(::my_block1()), a);
                std::cout << "my_block1 pass" << std::endl;
            }
            {
                int a[] = { 1,2,3,1,2,3,1,2,3 };
                test::single_pass_readable(in_block(::my_block2(3)), a);
                std::cout << "my_block2 pass" << std::endl;
            }
            {
                test::emptiness(in_block(::empty_block1()));
                std::cout << "empty_block1 pass" << std::endl;
                test::emptiness(in_block(::empty_block2()));
                std::cout << "empty_block2 pass" << std::endl;
            }
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "exception caught:";
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "unknown exception caught" << std::endl;
    }

    std::cout << "reference check begins" << std::endl;
    {
        int c = 1;
        BOOST_FOREACH (int& i, in_block(::reference_block())) {
            if (c == 1)
                BOOST_CHECK(&i == &g_int1);
            else if (c == 2)
                BOOST_CHECK(&i == &g_int2);
            else if (c == 3)
                BOOST_CHECK(&i == &g_int3);
            
            ++c;
        }

        BOOST_CHECK(c == 4);
    }
    {
        int c = 1;
        BOOST_FOREACH (int const& i, in_block(::const_reference_block())) {
            if (c == 1)
                BOOST_CHECK(&i == &g_cint1);
            else if (c == 2)
                BOOST_CHECK(&i == &g_cint2);
            else if (c == 3)
                BOOST_CHECK(&i == &g_cint3);
            
            ++c;
        }

        BOOST_CHECK(c == 4);
    }

    std::cout << "test ends.";
}
