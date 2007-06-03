#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/copied_to.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <pstade/oven/equals.hpp>
#include <iterator>
#include <string>
#include <pstade/oven/copy_range.hpp>
#include <pstade/is_same.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string   in("hello, copied_to!");
        std::string out1;
        std::string out2;
        std::string out3;
        in|copied_to(std::back_inserter(out1));
        in|copied_to(std::back_inserter(out2))|copied_to(std::back_inserter(out3));
        BOOST_CHECK( equals(in, out1) );
        BOOST_CHECK( equals(in, out2) );
        BOOST_CHECK( equals(in, out3) );
        
        std::vector<char> expected = in|copied;
        test::random_access_swappable(in|copied_to(std::back_inserter(out1)), expected);

#if 0 // rejected
        BOOST_CHECK( pstade::is_same(in, in|copied_to(std::back_inserter(out1))) );
#endif
    }
}
