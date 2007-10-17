#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/reset_assignment.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/shared_ptr.hpp>
#include <memory>


struct my
{
    explicit my() : m_x(999) { }
    explicit my(int x) : m_x(x) { }
    int m_x;

    PSTADE_RESET_ASSIGNMENT(my)

    void reset(int x)
    {
        m_x = x;
    }

    void reset()
    {
        m_x = 999;
    }
};


struct your
{
    explicit your() { }
    explicit your(std::auto_ptr<int> x) : m_x(x) { }
    boost::shared_ptr<int> m_x;

    PSTADE_MOVE_RESET_ASSIGNMENT(your)

    void reset(std::auto_ptr<int> x)
    {
        m_x = x;
    }

    void reset()
    {
        m_x.reset();
    }
};


inline
std::auto_ptr<int> make_auto(int i)
{
    return std::auto_ptr<int>(new int(i));
}


void pstade_minimal_test()
{
    {
        int i = 3;
        my m(i);
        BOOST_CHECK(m.m_x == 3);
        m = 6;
        BOOST_CHECK(m.m_x == 6);

        m = boost::none;
        BOOST_CHECK(m.m_x == 999);
    }
    {
        int const i = 3;
        my m(i);
        BOOST_CHECK(m.m_x == 3);
        m = 6;
        BOOST_CHECK(m.m_x == 6);

        m = boost::none;
        BOOST_CHECK(m.m_x == 999);
    }
    {
        my m(3);
        BOOST_CHECK(m.m_x == 3);
        m = 6;
        BOOST_CHECK(m.m_x == 6);

        m = boost::none;
        BOOST_CHECK(m.m_x == 999);
    }
    {
        my m(3);
        my m_(4);
        m = m_; // copy-assignment
        BOOST_CHECK(m.m_x == 4);
    }
    {
        your m(make_auto(3));
        BOOST_CHECK(*m.m_x == 3);
        m = make_auto(6);
        BOOST_CHECK(*m.m_x == 6);

        m = boost::none;
        BOOST_CHECK(!m.m_x);
    }
    {
        your m(make_auto(3));
        your m_(make_auto(5));
        m = m_; // copy-assignment
        BOOST_CHECK(*m.m_x == 5);
    }
}
