#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/biscuit.hpp>
#include <sstream>


using namespace pstade;
using namespace biscuit;


void test()
{
    typedef seq< any, before<eol> > parser;
    std::stringstream sout;
    biscuit::iterate< actor< parser, output_action > >(std::string("\nABC\n\nDEF\n"), sout, output_action());
    //biscuit::match< iteration<actor<parser, output_action>, output_action> >(std::string("ABC\nDEF"), sout);
    std::cout << sout.str();
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
