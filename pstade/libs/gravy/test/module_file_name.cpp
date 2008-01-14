#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/module_file_name.hpp>


#include <pstade/oven/copied.hpp>
#include <pstade/gravy/tstring.hpp>
#include <pstade/gravy/tiostream.hpp>
#include <pstade/gravy/c_str.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/equals.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    namespace gravy = pstade::gravy;
    using namespace gravy;

    {
        module_file_name mn;
        tstring str = mn|oven::copied;
        tcout << str << std::endl;
    }

    {
        module_file_name mn;
        c_str(mn);
    }
}
