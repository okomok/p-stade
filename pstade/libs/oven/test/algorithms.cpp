#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/algorithms.hpp>


#include <boost/range.hpp>
#include <string>

#include <pstade/oven/filter_range.hpp>
#include <pstade/oven/reverse_range.hpp>
#include <pstade/oven/share_range.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>


struct is_c
{
    bool operator()(char ch) const
    { return ch == 'c'; }
};


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src1("abcde");
    std::string src2("abcde");

    { // equals
        BOOST_CHECK( oven::equals(src1, src2) );
    }

    { // distance
        BOOST_CHECK( oven::distance(src1) == 5 );
    }

    {
        using namespace boost;

        std::string out;

        BOOST_FOREACH (char ch,
            new std::string("!exgnxxar ,xolxlexh") |
                shared |
                filtered(lambda::_1 != 'x') |
                reversed
        ) {
            out.push_back(ch);
        }

        BOOST_CHECK( out == "hello, range!" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
