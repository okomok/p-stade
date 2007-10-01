#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/cycled.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/reversed.hpp>
#include <pstade/oven/offset.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/egg/compose1.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <pstade/result_of_lambda.hpp> // composing lambdafunctor


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


template<class Iterator>
void check_cycle_count(Iterator first)
{
    BOOST_CHECK( oven::cycle_count<int>(first) == 5 );
    std::advance(first, 9);
    BOOST_CHECK( oven::cycle_count<int>(first) == 6);
}

template<class Iterator>
void check_cycle_count_10year(Iterator first)
{
    BOOST_CHECK( oven::cycle_count<int>(first) == 0 );
    BOOST_CHECK( oven::cycle_count<long>(first) == 0 );

    first += 24;
    BOOST_CHECK( oven::cycle_count<int>(first) == 1 );
    BOOST_CHECK( oven::cycle_count<long>(first) == 0 );

    first += 24;
    BOOST_CHECK( oven::cycle_count<int>(first) == 2 );
    BOOST_CHECK( oven::cycle_count<long>(first) == 0 );

    first += 24*362;
    BOOST_CHECK( oven::cycle_count<int>(first) == 364 );
    BOOST_CHECK( oven::cycle_count<long>(first) == 0 );

    first += 24;
    BOOST_CHECK( oven::cycle_count<int>(first) == 0 );
    BOOST_CHECK( oven::cycle_count<long>(first) == 1 );

    first += 24;
    BOOST_CHECK( oven::cycle_count<int>(first) == 1 );
    BOOST_CHECK( oven::cycle_count<long>(first) == 1 );
}



void pstade_minimal_test()
{

    {
        int a[] = { 1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4 };
        int b[] = { 1,2,3,4 };

        test::adaptor_random_access_constant_int(
            pstade::egg::compose1(
                lambda::bind(make_cycled, lambda::_1, 4), lambda::bind(make_cycled, lambda::_1, 2)
            ),
            a, b
        );
    }
    {
        std::string rng("12345*");
        std::string ans("345*12345*12345*12");
        std::vector<char> expected = ans|copied;

        test::random_access_constant(
            rng|cycled(2)|offset(-4, 2),
            expected
        );
    }
    {
        std::string rng("12345*");
        std::string ans("12345*12345*12345*12345*12345*123");
        std::vector<char> expected = ans|copied;

        test::forward_constant(
            rng|cycled|taken(6*5+3),
            expected
        );
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(3),
            std::string("xyzxyzxyz")
        ) );

        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(2)|cycled(3),
            std::string("xyz")|cycled(3)|cycled(2)
        ) );

        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(2)|cycled(3)|cycled(5),
            std::string("xyz")|cycled(3)|cycled(10)
        ) );

        BOOST_CHECK( 3*30 ==
            oven::distance(std::string("xyz")|cycled(2)|cycled(3)|cycled(5))
        );
    }

    {
/*
        BOOST_CHECK( oven::equals(
            std::string("abcd")|cycled(4)|reversed,
            std::string("dcbadcbadcbadcba")
        ) );
*/
        std::string src("abcd");
        BOOST_FOREACH (char ch, src|cycled(5)|reversed) {
            std::cout << ch << std::endl;;
        }

        BOOST_CHECK( oven::equals(
            std::string("xyz")|cycled(2)|cycled(3)|reversed,
            std::string("xyz")|cycled(3)|cycled(2)|reversed
        ) );
    }

    {
        std::string src("abcdefg");
        BOOST_CHECK( (src|cycled(5)).begin()[8] == 'b' );
        BOOST_CHECK( (src|cycled(5)|reversed).begin()[8] == 'f' );
    }
    {
        std::string src("abcdefg");
        ::check_cycle_count(boost::begin(src|cycled(5, 12)));
        ::check_cycle_count(boost::begin(src|cycled(5, 12)|identities|identities));
    }
    {
        int const day[24] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
        ::check_cycle_count_10year(boost::begin(day|cycled((int)0, (int)365)|cycled((long)0,(long)10)));
    }
}
