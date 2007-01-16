#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/generation.hpp>
#include <boost/none.hpp>


#include <cstdlib> // rand
#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/function_output_iterator.hpp>
#include <pstade/oven/counting.hpp>
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


#if 0 // impossible
// copy of an iterator would copy the address into itself.
// That's the dangling pointer!
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
            return result_type(); // == PSTADE_NULLPTR.

        return &m_state;
    }

    int m_state;
};
#endif


template< class T, class CharT, class Traits = std::char_traits<CharT> >
struct from_istream
{
    typedef std::basic_istream<CharT, Traits> istream_type;

    explicit from_istream(istream_type& is) :
        m_is(is)
    { }

    typedef boost::optional<CharT> result_type;

    result_type operator()()
    {
        T val;
        m_is >> val;
        if (!m_is)
            return result_type();

        return val;
    }

private:
    istream_type& m_is;
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

        BOOST_FOREACH (long x, oven::count_to(10)|generation(rand)) {
            std::cout << x << std::endl;
        }
    }
#endif

    {
        my_generator X(10);

        BOOST_FOREACH (int x, oven::generation(X)) {
            std::cout << x << std::endl;
        }

        BOOST_CHECK(X.m_state == 0);
    }

    {
        my_generator X(10);
        int ans[] = { 9,8,7,6,5,4,3,2,1 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::generation(X),
            expected
        ));

        BOOST_CHECK(X.m_state == 0);
    }

    {
        BOOST_FOREACH (long x, oven::generation_copied(rand_generator())) {
            std::cout << x << std::endl;
        }
    }

#if 0 // impossible
    {
        ptr_generator X(10);
        BOOST_FOREACH (int x, oven::generation(X)) {
            std::cout << x << std::endl;
        }
    }
    {
        ptr_generator X(10);
        int ans[] = { 9,8,7,6,5,4,3,2,1 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::generation(X),
            expected
        ));

        BOOST_CHECK(X.m_state == 0);
    }
#endif
    {
        std::string src("abcdefg");
        std::stringstream ss;
        ss << src;
        from_istream<char, char> X(ss);

        BOOST_CHECK( oven::equals(oven::generation(X), src) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
