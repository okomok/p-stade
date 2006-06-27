#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/locale_saver.hpp>


#include <iostream>


void test()
{
    using namespace pstade;

    // locale_saver ls("japanese"); // breaks VC8 wstreams.

    {
        locale_saver ls(std::locale("japanese")); // global
        BOOST_CHECK(( std::isalnum(L'‚P', std::locale()) ));
    }

    {
        locale_saver ls("japanese"); // global
        BOOST_CHECK(( std::isalnum(L'‚P', std::locale()) ));
    }

    {
        pstade::locale_saver ls(std::wcout, std::locale("japanese"));
        std::wcout << L"kkkkkkk‚¢‚Ù\n";
    }

    {
        pstade::locale_saver ls(std::wcout, "japanese");
        std::wcout << L"kkkkkkk‚¢‚Ù\n";
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
