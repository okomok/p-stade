#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream>
#include <string>
#include <vector>
#include <pstade/oven/algorithms.hpp>

#include <pstade/napkin.hpp>


void test_basic()
{
    using namespace pstade;

    {
        std::stringstream sout;

        napkin::ostream os1(sout);
        os1 << "xxx";
        BOOST_CHECK( sout.str() == "xxx" );

        os1.reset(sout);
        os1 << "xxx";
        BOOST_CHECK( sout.str() == "xxxxxx" );

        napkin::ostream os2;
        os2.reset(os1);
        os2 << "xxx";
        BOOST_CHECK( sout.str() == "xxxxxxxxx" );
    }

#if !defined(__MINGW32__)
    {
        std::wstringstream wsout;

        napkin::wostream wos1(wsout);
        wos1 << L"xxx";
        BOOST_CHECK( wsout.str() == L"xxx" );

        wos1.reset(wsout);
        wos1 << L"xxx";
        BOOST_CHECK( wsout.str() == L"xxxxxx" );

        napkin::ostream wos2;
        wos2.reset(wos1);
        wos2 << "xxx";
        BOOST_CHECK( wsout.str() == L"xxxxxxxxx" );
    }
#endif

    {
        std::string str;
        napkin::ostream os(str);
        os << "xxx";
        BOOST_CHECK( str == "xxx" );
    }

    {
        std::vector<char> vec;
        napkin::ostream os(vec);
        os << "xxx";
        BOOST_CHECK( oven::equals(vec, "xxx") );
    }
}


int test_main(int, char*[])
{
    ::test_basic();

    return 0;
}
