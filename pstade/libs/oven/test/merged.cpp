#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/merged.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/v1_tests.hpp"
#include "./detail/test.hpp"


#include <cctype>
#include <iostream>
#include <string>
#include <deque>
#include "./detail/v1_core.hpp"
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_tests.hpp"
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/rvalues.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


bool lt_nocase(char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}


template<class Range1, class Range2>
typename pstade::result_of<op_make_merged(Range1&, Range2&)>::type
make_merge_range_(Range1& rng1, Range2& rng2)
{
    return oven::make_merged(rng1, rng2);
}


void test1()
{
    {
        int A1[] = {1,6,7,10,14,17};
        int A2[] = {2,5,8,11,13,18};
        int A3[] = {3,4,9,12,15,16};
        int AA[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
        std::vector<int> expected = AA|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            A1|merged(A2)|merged(A3),
            expected
        ) );
    }
    {
        bool src0_[] = { false,false,false };
        std::vector<bool> src0 = src0_|copied;
        bool src1_[] = { false,true,true };
        std::vector<bool> src1 = src1_|copied;
        bool const ans[] = { false,false,false,false,true,true };
        std::deque<bool> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(src0|merged(src1), expected) );
    }
    {
        std::vector<int> expected = counting(0, 20)|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            counting(0, 10)|rvalues|merged(counting(char(10), char(20))),
            expected
        ) );
    }
    {
        std::string A1("abbbfH");
        std::string A2("ABbCDFFhh");
        std::string AA("aAbbbBbCDfFFHhh");
        std::vector<char> expected = AA|copied;
        BOOST_CHECK( !::lt_nocase('C', 'b') );
        BOOST_CHECK( is_sorted(A1, &::lt_nocase) );
        BOOST_CHECK( is_sorted(A2, &::lt_nocase) );
        BOOST_CHECK( is_sorted(AA, &::lt_nocase) );

        BOOST_CHECK( oven::test_Forward_Readable(
            A1|merged(A2, &::lt_nocase),
            expected
        ) );
    }
    {
        int A1[] = {1,3,5,7,9,11};
        int A2[] = {1,1,2,3,5,8,13};
        int AA[] = {1,1,1,2,3,3,5,5,7,8,9,11,13};

        BOOST_CHECK( oven::equals(A1|merged(A2), AA) );
        oven::copy(A1|merged(A2), stream_writer(std::cout));
    }
    {
        std::string A1("abbbfH");
        std::string A2("ABbCDFFhh");
        std::string AA("aAbbbBbCDfFFHhh");
        BOOST_CHECK( oven::equals(A1|merged(A2, &::lt_nocase), AA) );
        oven::copy(A1|merged(A2, &::lt_nocase), stream_writer(std::cout));
        // std::cout << std::endl;
        // oven::merge(A1, A2, stream_writer(std::cout), &lt_nocase); 
    }

    {
        BOOST_CHECK( oven::test_empty(
            std::string()|merged( std::string() )
        ) );

        BOOST_CHECK( equals(
            std::string("abcdefghi")|merged( std::string() ),
            std::string("abcdefghi")
        ) );

        BOOST_CHECK( equals(
            std::string()|merged( std::string("abcdefghi") ),
            std::string("abcdefghi")
        ) );
    }
}


void test2()
{
    namespace lambda = boost::lambda;
    {
        int b1[] = {1,3,5,7,9,11};
        int b2[] = {1,1,2,3,5,8,13};
        int a[] = {1,1,1,2,3,3,5,5,7,8,9,11,13};
        test::forward_constant(b1|merged(b2), a);
        test::equality(*test::new_vector<test::ncint>(b1)|merged(*test::new_list<test::ncint>(b2)), *test::new_vector<test::ncint>(a));
        test::forward_constant(b1|test::proxies|merged(b2)|const_refs, a); // proxy is turned to rvalue by detail::constand_reference.
    }
}


void pstade_minimal_test()
{
    ::test1();
    ::test2();
}
