#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/mb_encode_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/locale_saver.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

#if defined(BOOST_MSVC)
    {
        locale_saver loc("japanese");
        std::string mb("a‚ b‚¢c‚¤‚¦de");
        std::wstring wc(L"a‚ b‚¢c‚¤‚¦de");
        BOOST_CHECK(!oven::equals(mb, wc) );
        BOOST_CHECK( oven::equals(wc|mb_encoded, mb) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
