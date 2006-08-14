#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Radish
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/radish/bool_testable.hpp>


#include <boost/operators.hpp> // equality_comparable


struct my_bool_testable_t :
    pstade::radish::bool_testable< my_bool_testable_t >
{
    my_bool_testable_t(bool b) :
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


struct my_dool_testable_t :
    pstade::radish::bool_testable< my_dool_testable_t >,
    ::my_bool_testable_t
{
    my_dool_testable_t(bool b) :
        ::my_bool_testable_t(false), m_b(b)
    { }

private:
    bool m_b;

friend class pstade::radish::access;
    bool pstade_radish_bool() const
    {
        return m_b;
    }
};


struct my_equality_t :
    pstade::radish::bool_testable< my_equality_t >,
    boost::equality_comparable< my_equality_t >
{
    bool operator==(my_equality_t const&)
            const // don't forget 'const' to win against 'bool_testable' operators.
    {
        return true;
    }

friend class pstade::radish::access;
    bool pstade_radish_bool() const
    {
        return true;
    }
};


void test()
{
    {
        ::my_bool_testable_t b1(true);
        if (b1) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }

        ::my_bool_testable_t b2(false);
        if (!b2) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }

        if (b1 && b2) {
            BOOST_ASSERT(false);
        }
        else {
            ;
        }

        if (b1 && !b2) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }
    }

    {
        ::my_dool_testable_t d1(true);
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

        ::my_dool_testable_t d2(false);
        if (!d2) {
            ;
        }
        else {
            BOOST_ASSERT(false);
        }
    }

    {
        ::my_bool_testable_t b1(true), b2(false);

        // errors
        // b1 == b2;
        // b1 != b2;
        // b1 < b2;
    }

    {
        ::my_dool_testable_t d1(true), d2(false);

        // errors
        // d1 == d2;
        // d1 != d2;
        // b1 < b2;
    }

    {
        ::my_equality_t e1, e2;
        e1 == e2;
        e1 != e2;
        // e1 < e2; // error
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
