#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/map_values.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <map>
#include <vector>
#include <boost/foreach.hpp>


namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    std::map<char, int> b;
    b['a'] = 6; b['b'] = 1; b['c'] = 3; b['d'] = 7; b['e'] = 3;
    b['f'] = 2; b['g'] = 2; b['h'] = 1; b['i'] = 7; b['j'] = 2;
 
    std::vector<int> a;
    typedef std::pair<char const, int>& ref_t;
    BOOST_FOREACH (ref_t p, b) {
        a.push_back(p.second);
    }

    test::bidirectional_constant(b|elements_c<1>(), a);
    test::bidirectional_constant(b|map_values, a);
    test::bidirectional_swappable(b|map_values, a);
}
