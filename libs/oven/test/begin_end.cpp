#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/begin_end.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <algorithm>
#include <string>
#include <boost/range.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_TEST_IS_RESULT_OF((std::string::iterator), op_begin(std::string&))
PSTADE_TEST_IS_RESULT_OF((std::string::const_iterator), op_begin(std::string const&))
PSTADE_TEST_IS_RESULT_OF((std::string::const_iterator), op_begin(std::string))

PSTADE_TEST_IS_RESULT_OF((std::string::iterator), op_end(std::string&))
PSTADE_TEST_IS_RESULT_OF((std::string::const_iterator), op_end(std::string const&))
PSTADE_TEST_IS_RESULT_OF((std::string::const_iterator), op_end(std::string))


void pstade_minimal_test()
{
    {
        std::string rng1("hello, begin_end");
        std::string rng2(rng1);
        BOOST_CHECK( std::equal(begin(rng1), end(rng1), begin(rng2)) );
        BOOST_CHECK( std::equal(rng1|begin, rng1|end, rng2|begin) );
        BOOST_CHECK( std::equal(rng1|begin(), rng1|end(), rng2|begin()) );
    }
}
