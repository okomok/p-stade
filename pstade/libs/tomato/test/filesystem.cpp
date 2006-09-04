#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/filesystem.hpp>


#include <iostream>
#include <boost/foreach.hpp>
#include <pstade/oven.hpp>
#include <pstade/tomato/tstream.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;
    
    {
        tcout << "[all the files...]\n";
        find_file_range fnd(_T("*.*"));
        BOOST_FOREACH (WIN32_FIND_DATA const& dat, fnd) {
            tcout << dat.cFileName << std::endl;
        }
    }

    {
        tcout << "[directories...]\n";
        find_file_range fnd(_T("*.*"));
        BOOST_FOREACH (WIN32_FIND_DATA const& dat, fnd|oven::filtered(find_file_is_directory)) {
            tcout << dat.cFileName << std::endl;
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
