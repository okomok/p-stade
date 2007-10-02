#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/permuter.hpp>
#include <pstade/minimal_test.hpp>


#include <iterator>
#include <vector>
#include <algorithm>
#include <pstade/oven/equals.hpp>
#include "./detail/output_iterator.hpp"


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<int> vo;
        int const elems[] = {0,1,2,3,4,5,6,7,8,9};
        int const ids[] = {6,1,4,9,3};

        std::copy(boost::begin(ids), boost::end(ids), permuter(elems) |= std::back_inserter(vo));
        BOOST_CHECK( equals(vo, ids) );
        test::output_iterator(permuter(elems) |= std::back_inserter(vo), 7);
    }
}
