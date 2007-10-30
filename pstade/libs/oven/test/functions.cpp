#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/size.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/is_heap.hpp>
#include <pstade/oven/is_sorted.hpp>
#include <pstade/oven/forall.hpp>
#include <pstade/oven/exists.hpp>
#include <pstade/oven/do_iter_swap.hpp>
#include <pstade/oven/write.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <algorithm> // make_heap
#include <string>
#include <boost/range.hpp>
#include <pstade/result_of.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_TEST_IS_RESULT_OF((bool), T_equals(std::string&, std::string&))
PSTADE_TEST_IS_RESULT_OF((range_difference<std::string>::type), T_distance(std::string&))

PSTADE_TEST_IS_RESULT_OF((bool), T_is_sorted(std::string&))
PSTADE_TEST_IS_RESULT_OF((bool), T_is_heap(std::string&))

PSTADE_TEST_IS_RESULT_OF((bool), T_forall(std::string&))
PSTADE_TEST_IS_RESULT_OF((bool), T_exists(std::string&))

PSTADE_TEST_IS_RESULT_OF((void), T_do_iter_swap(int *, int*))


struct is_a
{
    bool operator()(char ch) const
    {
        return ch == 'a';
    }
};


void pstade_minimal_test()
{
    std::string src1("abcde");
    std::string src2("abcde");
    {
        BOOST_CHECK( equals(src1, src2) );
        BOOST_CHECK( equals(src1|identities(in_single_pass), src2|identities(in_single_pass)) );
    }
    {
        BOOST_CHECK( distance(src1) == 5 );
        BOOST_CHECK( distance(src1|identities(in_single_pass)) == 5 );
    }
    {
        BOOST_CHECK( (src1|distance) == 5 );
        BOOST_CHECK( (src1|identities(in_single_pass)|distance) == 5 );
        BOOST_CHECK( (src1|distance()) == 5 );
        BOOST_CHECK( (src1|identities(in_single_pass)|distance()) == 5 );
    }
    {
        int const rng[] = { 5,6,7,8,9,10,11,13,16 };
        int const rng_[]= { 0,3,7,1,3,6,1,3,3,6,1 };
        BOOST_CHECK( is_sorted(rng) );
        BOOST_CHECK( !is_sorted(rng_) );
    }
    {
        int rng[] = { 5,6,1,7,8,9,10,2,11,13,16 };
        BOOST_CHECK( !is_heap(rng) );
        std::make_heap(boost::begin(rng), boost::end(rng));
        BOOST_CHECK( is_heap(rng) );
    }
    {
        BOOST_CHECK( forall(std::string("aaaaaaaaaa"), is_a()) );
        BOOST_CHECK( !exists(std::string("bbbbbbbbb"), is_a()) );
    }
    {
        int rng[] = { 0, 1 };
        do_iter_swap(&rng[0], &rng[1]);
        BOOST_CHECK( rng[0] == 1 );
        BOOST_CHECK( rng[1] == 0 );
    }
    {
        int rng[] = { 0, 1 };
        write(boost::begin(rng), 50);
        BOOST_CHECK( rng[0] == 50 );
    }
    {
        BOOST_CHECK( size(std::string("bbbbbbbbb")) == 9 );
        BOOST_CHECK( (std::string("bbbbbbbbb")|size) == 9 );
        BOOST_CHECK( (std::string("bbbbbbbbb")|size()) == 9 );
    }
}
