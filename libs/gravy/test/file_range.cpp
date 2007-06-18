#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/file_range.hpp>


#include <vector>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copied_to.hpp>
#include <pstade/oven/algorithm.hpp>


void pstade_minimal_test()
{
    using namespace pstade;
    
    {
        gravy::ifile_range<> ifrng(_T("file_range_input.txt"));
        BOOST_CHECK(ifrng);
        BOOST_CHECK(ifrng.is_open());

        std::vector<char> vec = ifrng|oven::copied;
        BOOST_CHECK( oven::equals(ifrng, vec) );

        gravy::ofile_range<> ofrng(_T("file_range_output.txt"), oven::distance(ifrng));
        BOOST_CHECK(ofrng);
        BOOST_CHECK(ofrng.is_open());
        oven::copy(ifrng, boost::begin(ofrng));
    }

    gravy::ifile_range<> irng("file_range_input.txt");
    gravy::ifile_range<> irng2("file_range_output.txt");
    BOOST_CHECK( oven::equals(irng, irng2) );
}

