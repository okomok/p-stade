#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/foreach.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/typeof/std/string.hpp>
#include <boost/typeof/std/vector.hpp>
#include <string>


std::string g_singleton("01234");

std::string& make_string_once()
{
    static int count = 0;
    BOOST_CHECK(count == 0);
    ++count;
    return g_singleton;
}

std::string& make_const_string_once()
{
    static int count = 0;
    BOOST_CHECK(count == 0);
    ++count;
    return g_singleton;
}

template<class Range>
Range& make_string_once_tpl()
{
    static int count = 0;
    BOOST_CHECK(count == 0);
    ++count;
    return g_singleton;
}

template<class Range>
Range const& make_const_string_once_tpl()
{
    static int count = 0;
    BOOST_CHECK(count == 0);
    ++count;
    return g_singleton;
}


#define PSTADE_contents_check() \
    BOOST_CHECK(i == 0 ? v == '0' : true); \
    BOOST_CHECK(i == 1 ? v == '1' : true); \
    BOOST_CHECK(i == 2 ? v == '2' : true); \
    BOOST_CHECK(i == 3 ? v == '3' : true); \
    BOOST_CHECK(i == 4 ? v == '4' : true); \
    ++i; \
/**/


void test_()
{
    {
        std::string str;
        PSTADE_OVEN_FOREACH (v, str)
            (void)v, BOOST_CHECK(false);
    }
    {
        std::string str("a");
        PSTADE_OVEN_FOREACH (r, str) {
            r = 'b';
        }

        BOOST_CHECK( str == "b" );
    } 
    {
        std::string str("01234");
        int i = 0;
        PSTADE_OVEN_FOREACH (v, str) {
            PSTADE_contents_check()
        }
        BOOST_CHECK(i == 5);
    }
    {
        int i = 0;
        PSTADE_OVEN_FOREACH (v, ::make_string_once()) {
            PSTADE_contents_check()
        }
    }
    {
        int i = 0;
        PSTADE_OVEN_FOREACH (v, ::make_const_string_once()) {
            PSTADE_contents_check()
        }
    }
}


template<class Range>
void test_tpl()
{
    {
        Range str;
        PSTADE_OVEN_FOREACH_TPL (v, str)
            (void)v, BOOST_CHECK(false);
    }
    {
        Range str("a");
        PSTADE_OVEN_FOREACH_TPL (r, str) {
            r = 'b';
        }

        BOOST_CHECK( str == "b" );
    }
    {
        Range str("01234");
        int i = 0;
        PSTADE_OVEN_FOREACH_TPL (v, str) {
            PSTADE_contents_check()
        }
        BOOST_CHECK(i == 5);
    }

    {
        int i = 0;
        PSTADE_OVEN_FOREACH_TPL (v, ::make_string_once_tpl<Range>()) {
            PSTADE_contents_check()
        }
    }
    {
        int i = 0;
        PSTADE_OVEN_FOREACH_TPL (v, ::make_const_string_once_tpl<Range>()) {
            PSTADE_contents_check()
        }
    }
}


void test_nested()
{
    std::vector< std::string > vs1;
    vs1.push_back("01234");
    vs1.push_back("56789");
    vs1.push_back("abcde");

    char ans[3][5] = {
        { '0','1','2','3','4' },
        { '5','6','7','8','9' },
        { 'a','b','c','d','e' }
    };

    int c = 0;
    int i = 0;
    PSTADE_OVEN_FOREACH (s1, vs1) {
        int j = 0;
        PSTADE_OVEN_FOREACH (c1, s1) {
            BOOST_CHECK(ans[i][j] == c1);
            ++j;
            ++c;
        }
        ++i;
    }

    BOOST_CHECK(c == 5*3);
}


#if defined(PSTADE_OVEN_IN_BOOST)

    void test_boost()
    {
        {
            std::string str;
            BOOST_OVEN_FOREACH (v, str)
                (void)v, BOOST_CHECK(false);
        }
    }

    template<class Range>
    void test_boost_tpl()
    {
        {
            Range str;
            BOOST_OVEN_FOREACH_TPL (v, str)
                (void)v, BOOST_CHECK(false);
        }
    }

#endif


void test_break()
{
    {
        std::string str("01234");
        int i = 0;
        PSTADE_OVEN_FOREACH (v, str) {
            (void)v;

            if (i == 3)
                break;

            ++i;
        }
        BOOST_CHECK(i == 3);
    }
}


void pstade_minimal_test()
{
    ::test_();
    ::test_tpl<std::string>();
    ::test_nested();
    ::test_break();

#if defined(PSTADE_OVEN_IN_BOOST)
    ::test_boost();
    ::test_boost_tpl<std::string>();
#endif
}
