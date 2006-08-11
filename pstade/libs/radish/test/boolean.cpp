#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Radish
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/radish/boolean.hpp>


struct my_boolean_t :
    pstade::radish::boolean< my_boolean_t >
{
    my_boolean_t(bool b) :
        m_b(b)
    { }

private:
    bool m_b;

friend class pstade::radish::access;
    bool pstade_radish_bool() const
    {
        return m_b;
    }
};


void test()
{
    ::my_boolean_t b1(true);
    BOOST_ASSERT(b1);
    ::my_boolean_t b2(false);
    BOOST_ASSERT(!b2);
}

int test_main(int, char*[])
{
    ::test();
    return 0;
}
