#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/find_file_range.hpp>
#include <pstade/gravy/find_file_predicates.hpp>


#include <iostream>
#include <boost/foreach.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/gravy/tiostream.hpp>


void pstade_minimal_test()
{
    using namespace pstade;
    
    {
        gravy::tcout << "[all the files...]\n";
        gravy::find_file_range fnd(_T("*.*"));
        BOOST_FOREACH (WIN32_FIND_DATA const& dat, fnd) {
            gravy::tcout << dat.cFileName << std::endl;
        }
    }

    {
        gravy::tcout << "[directories...]\n";
        gravy::find_file_range fnd(_T("*.*"));
        BOOST_FOREACH (WIN32_FIND_DATA const& dat, fnd|oven::filtered(gravy::find_file_is_directory)) {
            gravy::tcout << dat.cFileName << std::endl;
        }
    }
}
