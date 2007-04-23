#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/algorithm/parse.hpp>


#include <string>
#include <pstade/oven/equals.hpp>


#include <pstade/biscuit/alias.hpp>
#include <pstade/oven/alias.hpp>
using namespace biscuit;


struct inc_and_less_than_5
{
    bool operator()(int& i)
    {
        ++i;
        return i < 5;
    }
};


struct init_to_0
{
    void operator()(int& i)
    {
        i = 0;
    }
};


struct less_than_5
{
    bool operator()(int& i)
    {
        return i < 5;
    }
};


struct inc
{
    void operator()(int& i)
    {
        ++i;
    }
};


void test()
{
    {
        int count = 0;

        BOOST_CHECK(( oven::equals(std::string("01234"),
            biscuit::parse<
                do_<
                    any,
                    inc_and_less_than_5
                >
            >(std::string("0123456798"), count)
        ) ));
    }

    {
        int count = 100;

        BOOST_CHECK(( oven::equals(std::string("01234"),
            biscuit::parse<
                for_< init_to_0, less_than_5, inc,
                    any
                >
            >(std::string("0123456798"), count)
        ) ));
    }

    {
        int count = 3;

        BOOST_CHECK(( oven::equals(std::string("0"),
            biscuit::parse<
                if_< less_than_5,
                    any
                >
            >(std::string("0123456798"), count)
        ) ));
    }

    {
        int count = 0;

        BOOST_CHECK(( oven::equals(std::string("0123"),
            biscuit::parse<
                while_< inc_and_less_than_5,
                    any
                >
            >(std::string("0123456798"), count)
        ) ));
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
