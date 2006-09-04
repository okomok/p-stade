#include <pstade/vodka/drink.hpp>
#include <boost/test/test_tools.hpp>


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lime/node_facade.hpp>
#include <pstade/lime/load.hpp>
#include <pstade/lime/save.hpp>


#include <fstream>
#include <iostream>
#include <string>
#include <pstade/oven.hpp>
#include <pstade/wine.hpp>


void test()
{
    using namespace pstade;

    typedef lime::node_facade<int> my_node;

    std::cout << "<lime_test>";

    try {

        std::string iname("sample.xml");
        std::cout << "<input-file>" << iname << "</input-file>";

        std::string oname = iname + ".out";
        std::ofstream fout(oname.c_str(), std::ios::binary);
        pstade::require(fout, "good output file: " + oname);

        ustring tmp = // copy for speed
            oven::file_range<utf8cp_t>(iname)
                | oven::utf8_decoded
                | oven::copied;

        my_node root;
        lime::load(root, tmp);

        lime::save(
            root.front(),
            oven::utf8_encoder(oven::stream_outputter(fout))
        );

    }
    catch (std::exception& err) {
        std::cout << "<error>" << err.what() << "</error>\n";
    }

    std::cout << "</lime_test>";
}


#define BOOST_LIB_NAME boost_unit_test_framework
#define BOOST_LIB_DIAGNOSTIC yes
#include <boost/config/auto_link.hpp>
#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;


test_suite* init_unit_test_suite(int, char *[])
{
    test_suite* test = BOOST_TEST_SUITE( "Lime Basic Test Suite" );

    test->add( BOOST_TEST_CASE( &::test ) );


    return test;
}
