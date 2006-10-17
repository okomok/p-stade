#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/generate_range.hpp>
#include <boost/none.hpp>


#include <cstdlib> // rand
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/function_output_iterator.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/nullptr.hpp>


struct my_generator :
    private boost::noncopyable
{
    my_generator(int last) :
        m_state(last)
    { }

    typedef boost::optional<int const&> result_type;

    result_type operator()()
    {
        --m_state;

        if (m_state == 0)
            return result_type();

        return m_state;
    }

    int m_state;
};


struct rand_generator
{
    typedef boost::optional<long> result_type;

    result_type operator()()
    {
        long result = std::rand();
        if (result % 3 == 0)
            return result_type();

        return result;
    }
};


struct ptr_generator :
    private boost::noncopyable
{
    ptr_generator(int last) :
        m_state(last)
    { }

    typedef int const *result_type;

    result_type operator()()
    {
        --m_state;

        if (m_state == 0)
            return PSTADE_NULLPTR;

        return &m_state;
    }

    int m_state;
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

#if 0 // rejected interface
    {
        // Workaround:
        // GCC cannot order const and non-const reference to function,
        // with 'std::'.
        // (Note that const-qualified function type is illegal, but GCC allows.)
        // Now it seems impossible to support a function reference...
        using std::rand;

        BOOST_FOREACH (long x, oven::from_0_to(10)|generation(rand)) {
            std::cout << x << std::endl;
        }
    }
#endif

    {
        my_generator X(10);

        BOOST_FOREACH (int x, oven::generation<my_generator&>(X)) {
            std::cout << x << std::endl;
        }

        BOOST_CHECK(X.m_state == 0);
    }

    {
        my_generator X(10);
        int ans[] = { 9,8,7,6,5,4,3,2,1 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::generation<my_generator&>(X),
            expected
        ));

        BOOST_CHECK(X.m_state == 0);
    }

    {
        BOOST_FOREACH (long x, oven::generation(rand_generator())) {
            std::cout << x << std::endl;
        }
    }


    {
        ptr_generator X(10);
        BOOST_FOREACH (int x, oven::generation<ptr_generator&>(X)) {
            std::cout << x << std::endl;
        }
    }
    {
        ptr_generator X(10);
        int ans[] = { 9,8,7,6,5,4,3,2,1 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::generation<ptr_generator&>(X),
            expected
        ));

        BOOST_CHECK(X.m_state == 0);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
