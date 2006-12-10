#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/always_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>


template< class T >
void can_take(T&)
{ };


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string src1("unused");
        std::string src2("hello, always_range!");
        std::vector<char> expected = src2|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            src1|always(src2), expected
        ) );
    }
    {
        ::can_take(std::string()|always(std::string()));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
