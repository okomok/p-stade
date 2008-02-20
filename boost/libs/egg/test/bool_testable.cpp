

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <boost/egg/detail/bool_testable.hpp>


#include <iostream>
#include <boost/operators.hpp> // equality_comparable


struct my_bool_testable_t :
    boost::egg::details::bool_testable< my_bool_testable_t >
{
    my_bool_testable_t(bool b) :
        m_b(b)
    { }

    struct safe_bool_helper { int x; };
    typedef int safe_bool_helper::* safe_bool;
    safe_bool is_good_safe_bool() const
    {
        return m_b ? &safe_bool_helper::x : 0;
    }

    bool is_good() const
    {
        return m_b;
    }

    operator boost::egg::details::safe_bool() const
    {
        return boost::egg::details::make_safe_bool(m_b);
    }

private:
    bool m_b;
};


struct my_dool_testable_t :
    boost::egg::details::bool_testable< my_dool_testable_t >,
    ::my_bool_testable_t
{
    my_dool_testable_t(bool b) :
        ::my_bool_testable_t(false), m_b(b)
    { }

    operator boost::egg::details::safe_bool() const
    {
        return boost::egg::details::make_safe_bool(m_b);
    }

private:
    bool m_b;
};


struct my_equality_t :
    boost::egg::details::bool_testable< my_equality_t >,
    boost::equality_comparable< my_equality_t >
{
    bool operator==(my_equality_t const&)
            const // don't forget 'const' to win against 'bool_testable' operators.
    {
        return true;
    }

    operator boost::egg::details::safe_bool() const
    {
        return boost::egg::details::safe_true;
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
#if 1
        if (d1) { // *no longer* ambiguous!
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
        BOOST_CHECK( e1 ? true : false );
        BOOST_CHECK( e2 ? true : false );
        // e1 < e2; // error
    }

    {
        if (boost::egg::details::safe_true)
            BOOST_CHECK(true);
        else
            BOOST_CHECK(false);

        if (boost::egg::details::safe_false)
            BOOST_CHECK(false);
        else
            BOOST_CHECK(true);
    }
}


void test_normal()
{
    my_bool_testable_t b(true);
    if (b.is_good())
        pstade::used(b);
}

void test_idiom()
{
    my_bool_testable_t b(true);
    if (b.is_good_safe_bool())
        pstade::used(b);
}

void test_testable()
{
    my_bool_testable_t b(true);
    if (b)
        pstade::used(b);
}


void egg_test()
{
    ::test();
    ::test_normal();
    ::test_idiom();
    ::test_testable();
}
