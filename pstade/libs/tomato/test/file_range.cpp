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


#include <pstade/tomato/file_range.hpp>


#include <iostream>
#include <boost/foreach.hpp>
#include <pstade/garlic.hpp>
#include <pstade/oven.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;
    
    {
        ifile_range<> frng(_T("test.txt"));

        std::vector<char> vec;
        oven::copy(frng, garlic::back_inserter(vec));
        BOOST_CHECK( oven::equals(frng, vec) );

        BOOST_FOREACH (char ch, frng) {
            std::cout << ch;
        }

        oven::copies(frng, ofile_range<>(_T("test_out.txt"), oven::distance(frng)));
    }

    BOOST_CHECK( oven::equals( ifile_range<>("test.txt"), ifile_range<>("test_out.txt")) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
