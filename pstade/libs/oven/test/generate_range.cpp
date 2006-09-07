#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/generate_range.hpp>


#include <cstdlib> // rand
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/function_output_iterator.hpp>
#include <pstade/oven/counting_range.hpp>

class my_generator
{
public:
    typedef int result_type;
    my_generator() : m_state(0) { }
    int operator()() const { return ++m_state; }
    mutable int m_state;
};


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        // Workaround:
        // GCC cannot order const and non-const reference to function,
        // with 'std::'.
        // (Note that const-qualified function type is illegal, but GCC allows.)
        // Now it seems impossible to support a function reference...
        using std::rand;

        BOOST_FOREACH (long x, oven::int_range(3, 10)|generated(rand)) {
            std::cout << x << std::endl;
        }
    }

    {
        ::my_generator gen;

        BOOST_FOREACH (int x, oven::int_range(3, 10)|generated(gen)) {
            (void)x;
        }
        BOOST_CHECK(gen.m_state == 0);

        BOOST_FOREACH (int x, oven::int_range(3, 10)|generated(boost::ref(gen))) {
            (void)x;
        }
        BOOST_CHECK(gen.m_state == 7);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
