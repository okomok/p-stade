#include <pstade/vodka/drink.hpp>


// PStade.Radish
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/radish/arrow_result.hpp>
#include <pstade/minimal_test.hpp>


#include <string>


using namespace pstade;


struct my
{
    radish::arrow_result<std::string &>::type operator->()
    {
        return m_str;
    }

    radish::arrow_result<std::string const &>::type operator->() const
    {
        return m_str;
    }

    std::string m_str;
};

struct v_my
{
    radish::arrow_result<std::string>::type operator->()
    {
        return m_str;
    }

    std::string m_str;
};


struct void_my
{
    radish::arrow_result<void>::type operator->()
    {
        return ret_void();
    }

    void ret_void()
    {
    }
};


void pstade_minimal_test()
{
    {
        my a = { "hello" };
        BOOST_CHECK(a->size() == 5);
    }
    {
        my const a = { "hello" };
        BOOST_CHECK(a->size() == 5);
    }
    {
        v_my a = { "hello" };
        BOOST_CHECK(a->size() == 5);
    }
    {
        void_my a;
        (void)a;
    }
}
