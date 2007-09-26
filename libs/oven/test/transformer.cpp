#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/transformer.hpp>
#include <pstade/minimal_test.hpp>


#include <algorithm>
#include <pstade/oven/equals.hpp>


struct my_add
{
    int operator()(int i) const
    {
        return i + 1;
    }
};


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int const b[] = {0,1,2,3,4,5,6,7,8,9};
    int const a[] = {1,2,3,4,5,6,7,8,9,10};
    {
        int o[] = {9,8,7,6,5,4,3,2,1,0};
        std::copy(boost::begin(b), boost::end(b), transformer(my_add())|=&o[0]);
        BOOST_CHECK( oven::equals(o, a) );
    }
}
