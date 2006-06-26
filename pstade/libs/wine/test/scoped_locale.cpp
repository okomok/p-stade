#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <pstade/scoped_locale.hpp>


#include <iostream>


void test()
{
    using namespace pstade;

    // scoped_locale loc_("japanese"); // breaks VC8 wstreams.

    {
        scoped_locale loc(std::locale("japanese")); // global
        BOOST_CHECK(( std::isalnum(L'‚P', loc) ));
    }

    {
        scoped_locale loc("japanese"); // global
        BOOST_CHECK(( std::isalnum(L'‚P', loc) ));
    }

    {
        pstade::scoped_locale loc(std::wcout, std::locale("japanese"));
        std::wcout << L"kkkkkkk‚¢‚Ù\n";
    }

    {
        pstade::scoped_locale loc(std::wcout, "japanese");
        std::wcout << L"kkkkkkk‚¢‚Ù\n";
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
