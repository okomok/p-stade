#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/dropped_while.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <pstade/oven/regular.hpp>
#include <pstade/oven/equals.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    namespace lambda = boost::lambda;
    using namespace oven;

    {
        int a[] = { 2,3,4,5,1,6,3,1,3 };
        int b[] = { 1,1,1,1,1,2,3,4,5,1,6,3,1,3 };
        test::adaptor_random_access_swappable_int(
            lambda::bind(make_dropped_while, lambda::_1, regular(lambda::_1 == 1)),
            a, b
        );
    }
    {
        int a[] = { 1,1,1,1,1,2,3,4,5,1,6,3,1,3 };
        int b[] = { 1,1,1,1,1,2,3,4,5,1,6,3,1,3 };
        test::adaptor_random_access_swappable_int(
            lambda::bind(make_dropped_while, lambda::_1, regular(lambda::_1 == 9)),
            a, b
        );
    }

    std::string rng("11111234516313!");
    {
        test::emptiness(
            rng|dropped_while(regular(lambda::_1 != '9'))
        );

        test::emptiness(
            std::string()|dropped_while(regular(lambda::_1 != '9'))
        );
    }
    {
        std::string src("11111234516313!");

        BOOST_CHECK( oven::equals(
            src|dropped_while(regular(lambda::_1 == '1')),
            std::string("234516313!")
        ) );

        BOOST_CHECK( oven::equals(
            src|dropped_while(regular(lambda::_1 == '9')),
            src
        ) );

        BOOST_CHECK( oven::equals(
            src|dropped_while(regular(lambda::_1 != '9')),
            std::string("")
        ) );
    }
}
