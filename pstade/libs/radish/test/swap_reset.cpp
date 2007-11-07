#include <pstade/vodka/drink.hpp>


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/radish/swap_reset.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/shared_ptr.hpp>
#include <memory>
#include <pstade/egg/do_swap.hpp>


struct my
{
    explicit my() : m_x(999) { }
    explicit my(int x) : m_x(x) { }
    int m_x;

    typedef my pstade_radish_this_type;
    #include PSTADE_RADISH_SWAP_RESET()

    void swap(my& that)
    {
        pstade::egg::do_swap(m_x, that.m_x);
    }
};


struct your
{
    explicit your() { }
    explicit your(std::auto_ptr<int> x) : m_x(x) { }
    boost::shared_ptr<int> m_x;

    typedef your pstade_radish_this_type;
    #include PSTADE_RADISH_MOVE_SWAP_RESET()

    void swap(your& that)
    {
        m_x.swap(that.m_x);
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
        m.reset(6);
        BOOST_CHECK(m.m_x == 6);

        m.reset();
        BOOST_CHECK(m.m_x == 999);
    }
    {
        int const i = 3;
        my m(i);
        BOOST_CHECK(m.m_x == 3);
        m.reset(6);
        BOOST_CHECK(m.m_x == 6);

        m.reset();
        BOOST_CHECK(m.m_x == 999);
    }
    {
        my m(3);
        BOOST_CHECK(m.m_x == 3);
        m.reset(6);
        BOOST_CHECK(m.m_x == 6);

        m.reset();
        BOOST_CHECK(m.m_x == 999);
    }
    {
        my m(3);
        my m_(4);
        m.reset(m_); // copy
        BOOST_CHECK(m.m_x == 4);
    }
    {
        your m(make_auto(3));
        BOOST_CHECK(*m.m_x == 3);
        m.reset(make_auto(6));
        BOOST_CHECK(*m.m_x == 6);

        m.reset();
        BOOST_CHECK(!m.m_x);
    }
    {
        your m(make_auto(3));
        your m_(make_auto(5));
        m.reset(m_); // copy
        BOOST_CHECK(*m.m_x == 5);
    }
}
