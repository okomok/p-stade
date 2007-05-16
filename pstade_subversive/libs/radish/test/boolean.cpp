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


struct my_doolean_t :
    pstade::radish::boolean< my_doolean_t >,
    ::my_boolean_t
{
    my_doolean_t(bool b) :
        ::my_boolean_t(false), m_b(b)
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
    {
        ::my_boolean_t b1(true);
        if (b1) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }

        ::my_boolean_t b2(false);
        if (!b2) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }
    }

    {
        ::my_doolean_t d1(true);
#if 0
        if (d1) { // ambiguous!
            ;
        }
        else {
            BOOST_ASSERT(false);
        }
#endif
        if (!!d1) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }

        ::my_doolean_t d2(false);
        if (!d2) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
