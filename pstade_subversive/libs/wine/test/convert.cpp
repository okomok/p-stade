#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/convert.hpp>


#include <boost/utility/result_of.hpp>


using namespace pstade;


struct my
{
    /*implicit*/ my(int i)
        : m_i(i)
    { }

    int m_i;
};


void test()
{
    {
        boost::result_of<op_convert<my>(int)>::type
            r = pstade::convert<my>(10);
        BOOST_CHECK(r.m_i == 10);
    }
    {
        boost::result_of<op_convert<char>(int)>::type
            r = pstade::convert<char>(10);
        BOOST_CHECK(r == char(10));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
