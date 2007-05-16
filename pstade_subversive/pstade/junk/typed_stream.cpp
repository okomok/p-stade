#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/typed_stream.hpp>


#include <iostream>
#include <sstream>


void test()
{
    using namespace pstade;

    {
        typed_istream<std::string> is(std::cin);
        std::string s;
        is >> s;
    }

    {
        typed_ostream<std::string> os(std::cout);
        os << "hello";
    }

    {
        std::stringstream ss;
        typed_iostream<std::string> ios(ss);
        ss << "hello";
        std::string o;
        ss >> o;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
