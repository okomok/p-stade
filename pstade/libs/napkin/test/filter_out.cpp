#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <string>
#include <sstream>

#include <pstade/napkin.hpp>

struct foo_t
{
    bool operator()(const char *psz)
    {
        std::string tmp(psz);
        if (tmp != "aa")
            return true;

        return false;
    }
};

struct bar_t
{
    bool operator()(const char *psz)
    {
        std::string tmp(psz);
        if (tmp != "bb")
            return true;

        return false;
    }
};


void test_filter_out()
{
    using namespace pstade;

    std::stringstream sout;
    foo_t foo;
    bar_t bar;

    napkin::ostream os1(sout);

    napkin::filter_out<foo_t> fout1(foo, os1);
    napkin::filter_out<bar_t> fout2(bar, fout1);

    napkin::ostream os2(fout2);
    os2 << "cc" << "aa" << 'x' << "dd" << "bb" << 12 << "aa";

    BOOST_CHECK( sout.str() == "ccxdd12" );
}


int test_main(int, char*[])
{
    ::test_filter_out();

    return 0;
}
