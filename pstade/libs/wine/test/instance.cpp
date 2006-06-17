#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include <pstade/comma_protect.hpp>


struct aaa
{
    aaa(char, int, double)
    { }
};


struct bbb : private boost::noncopyable
{
    bbb(std::string str) :
        m_str(str)
    { }

    std::string m_str;
};


PSTADE_INSTANCE(int, x, value)
PSTADE_INSTANCE(const int, cx, value)
PSTADE_INSTANCE(aaa, a, ('a')(10)(3.5))
PSTADE_INSTANCE(bbb, b, ("hello"))


PSTADE_INSTANCE(int, x1, (12))
PSTADE_INSTANCE(int const, cx1, (12))


PSTADE_INSTANCE(const char *, sz, ("hello"))
PSTADE_INSTANCE(std::string, str, (sz))
PSTADE_INSTANCE(const std::string, cstr, (str))
PSTADE_INSTANCE(const std::string, cstr_, value)
PSTADE_INSTANCE(pstade::comma_protect<void(std::map<int, int>)>::type, map1_, value)
PSTADE_INSTANCE((std::map<int, int>), map2_, value)


void test()
{
    BOOST_CHECK(x == 0);
    BOOST_CHECK(cx == 0);
    x = x1;
    BOOST_CHECK(x == x1);
    BOOST_CHECK(x1 == cx1);
    BOOST_CHECK(b.m_str == "hello");
    BOOST_CHECK(x1 == 12);
    BOOST_CHECK(str == sz);
    BOOST_CHECK(cstr == sz);
    map1_[12] = 13;
    map2_[12] = 13;
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
