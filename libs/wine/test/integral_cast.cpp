#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>


#include <pstade/result_of.hpp>

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
    unsigned int ui = 0;
    signed int i = 0;

    ui = pstade::op_integral_cast<signed int>()(i);
    ui = pstade::integral_cast<signed int>(i);

    ui = i|to_integer;
}


void test_()
{
    try {
        pstade::result_of<op_integral_cast<short>(long)>::type
            s = pstade::integral_cast<short>(70000L);
            (void)s;
    }
    catch (boost::bad_numeric_cast)
    {
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
