#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/indirecter.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/outdirected.hpp>
#include "./detail/output_iterator.hpp"


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int const b[] = {0,1,2,3,4,5,6,7,8,9};
    {
        int o[] = {9,8,7,6,5,4,3,2,1,0};
        copy(b|outdirected, indirecter|=&o[0]);
        BOOST_CHECK( oven::equals(o, b) );
        test::output_iterator(indirecter|=&o[0], &b[0]);
    }
}
