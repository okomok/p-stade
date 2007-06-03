#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/dropped.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <string>
#include <vector>
#include <pstade/result_of_lambda.hpp>
#include <boost/range.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/compose.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/identities.hpp>


void pstade_minimal_test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 6,8,5,3,1,2,3,4,56,7,34 };
        int b[] = { 6,2,3,1,2,3,6,8,5,3,1,2,3,4,56,7,34 };

        test::adaptor_random_access_constant_int(
            pstade::compose(
                lambda::bind(make_dropped, lambda::_1, 5),
                lambda::bind(make_dropped, lambda::_1, 1)
            ),
            a, b
        );

        test::adaptor_random_access_swappable_int(
            pstade::compose(
                lambda::bind(make_dropped, lambda::_1, 4),
                lambda::bind(make_dropped, lambda::_1, 2)
            ),
            a, b
        );

        test::emptiness(
            b|dropped(7)|dropped(500)
        );

        test::emptiness(
            b|dropped(distance(b))
        );
    }
    {
        std::string src("hello, drop_range!");
        BOOST_CHECK( oven::equals(src|dropped(7)|dropped(5), std::string("range!")) );
        BOOST_CHECK( oven::equals(src|dropped(7000), std::string()) );
    }
    {
        std::string src("hello, drop_range!");
        BOOST_CHECK( oven::equals(src|identities(in_single_pass)|dropped(7)|dropped(5), std::string("range!")) );
        BOOST_CHECK( oven::equals(src|identities(in_single_pass)|dropped(7000), std::string()) );
        BOOST_CHECK( oven::equals(src|identities(in_single_pass)|dropped(distance(src)), std::string()) );
    }
    {
        test::emptiness(
            std::string()|dropped(0)
        );
        test::emptiness(
            std::string()|dropped(1)
        );
        test::emptiness(
            std::string()|dropped(100)
        );
    }
    {
        test::emptiness(
            std::string()|identities(in_single_pass)|dropped(0)
        );
        test::emptiness(
            std::string()|identities(in_single_pass)|dropped(1)
        );
        test::emptiness(
            std::string()|identities(in_single_pass)|dropped(100)
        );
    }
}
