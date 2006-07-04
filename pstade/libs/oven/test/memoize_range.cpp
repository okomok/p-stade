#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/memoize_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/algorithms.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/filter_range.hpp>

#include <iterator>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;
    namespace bll = boost::lambda;

    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            oven::equals(answer,
                src |
                    filtered(bll::_1 != 'x') |
                    memoized |
                    copied(std::back_inserter(s1)) |
                    filtered(bll::_1 != 'a') |
                    memoized |
                    copied(std::back_inserter(s2))
            )
        ));

        BOOST_CHECK( s1 == "aaabbb" );
        BOOST_CHECK( s2 == answer );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
