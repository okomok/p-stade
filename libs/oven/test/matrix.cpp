#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/vodka/drink_loss_of_data.hpp>


#include <pstade/oven/matrix.hpp>
#include "./detail/v1_tests.hpp"


#include <boost/foreach.hpp>
#include <pstade/oven/at.hpp>
#include <pstade/oven/detail/before_stable_partition.hpp>
#include <pstade/oven/io.hpp>
#include <iostream>


void test_2d()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int arr[5][7] = {
        { 0, 1, 2, 3, 4, 5, 6},
        {10,20,30,40,50,60,70},
        { 7, 8, 9,10,11,12,13},
        {78,13,16,34,22,16,77},
        {90,91,92,93,94,95,96}
    };

    int src[5*7] = {
         0, 1, 2, 3, 4, 5, 6,
        10,20,30,40,50,60,70,
         7, 8, 9,10,11,12,13,
        78,13,16,34,22,16,77,
        90,91,92,93,94,95,96
    };

    {
        std::vector<int> rng = src|copied;
        int ans[] = { 7, 8, 9,10,11,12,13 };
        std::vector<int> expected = ans|copied;

        //std::cout << ( rng|rows(5, 7) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|rows(5, 7)|at(2),
            expected
        ) );

        BOOST_CHECK( (rng|rows(5, 7)|at(2)|at(5)) == arr[2][5] );
        BOOST_CHECK( (rng|rows(5, 7))[2][5] == arr[2][5] );
        BOOST_CHECK( arr[2][5] == 12 );

        BOOST_CHECK( (rng|matrix(5, 7)|at(2)|at(5)) == arr[2][5] );
        BOOST_CHECK( (rng|matrix(5, 7))[2][5] == arr[2][5] );
    }
    {
        std::vector<int> rng = src|copied;
        int ans[] = { 5,60,12,16,95 };
        std::vector<int> expected = ans|copied;

        //std::cout << ( rng|columns(5, 7) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|columns(5, 7)|at(5) PSTADE_OVEN_BEFORE_STABLE_PARTITION,
            expected
        ) );

        BOOST_CHECK( (rng|columns(5, 7)|at(5)|at(2)) == arr[2][5] );
        BOOST_CHECK( arr[2][5] == 12 );
    }
}


void test_3d()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int arr[3][5][7] = {
        {
            { 0, 1, 2, 3, 4, 5, 6},
            {10,20,30,40,50,60,70},
            { 7, 8, 9,10,11,12,13},
            {78,13,16,34,22,16,77},
            {90,91,92,93,94,95,96}
        },
        {
            { 0, 1, 2, 3, 4, 5, 6},
            {86,26,36,46,56,66,76},
            { 7, 8, 9,86,88,82,83},
            {78,83,86,34,22,86,77},
            {96,98,92,93,94,95,96}
        },
        {
            { 0, 1, 2, 3, 4, 5, 6},
            {11,21,31,41,51,61,71},
            { 7, 8, 2,11,11,12,13},
            {78,13,16,34,22,16,77},
            {21,21,22,23,24,25,26}
        }
    };

    int src[3*5*7] = {
             0, 1, 2, 3, 4, 5, 6,
            10,20,30,40,50,60,70,
             7, 8, 9,10,11,12,13,
            78,13,16,34,22,16,77,
            90,91,92,93,94,95,96
        ,
        
             0, 1, 2, 3, 4, 5, 6,
            86,26,36,46,56,66,76,
             7, 8, 9,86,88,82,83,
            78,83,86,34,22,86,77,
            96,98,92,93,94,95,96
        ,
        
             0, 1, 2, 3, 4, 5, 6,
            11,21,31,41,51,61,71,
             7, 8, 2,11,11,12,13,
            78,13,16,34,22,16,77,
            21,21,22,23,24,25,26
    };

    BOOST_CHECK( (&arr[0][0][0])[35+9] == 36 );

    {
        std::vector<int> rng = src|copied;
        int ans[] = { 78,83,86,34,22,86,77 };
        std::vector<int> expected = ans|copied;

        std::cout << (rng|matrix3d(3, 5, 7));

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|matrix3d(3, 5, 7)|at(1)|at(3),
            expected
        ) );

        BOOST_CHECK( (rng|matrix3d(3, 5, 7)|at(1)|at(2)|at(3)) == arr[1][2][3] );
        BOOST_CHECK( (rng|matrix3d(3, 5, 7))[1][2][3] == arr[1][2][3] );
        BOOST_CHECK( arr[1][2][3] == 86 );
        
        BOOST_CHECK( (rng|matrix(3, 5, 7)|at(1)|at(2)|at(3)) == arr[1][2][3] );
        BOOST_CHECK( (rng|matrix(3, 5, 7))[1][2][3] == arr[1][2][3] );
    }
    {
        std::vector<int> rng = src|copied;

        typedef boost::
            result_of<op_make_matrix(std::vector<int>&, int, int, int)>::type
        rng3d_t;
        rng3d_t rng3d = make_matrix(rng, 3, 5, 7);

        int i = 0;
        BOOST_FOREACH (range_value<rng3d_t>::type rng2d, rng3d) {
            int j = 0;
            BOOST_FOREACH (range_value<range_value<rng3d_t>::type>::type rng1d, rng2d) {
                int k = 0;
                BOOST_FOREACH (int& x, rng1d) {
                    BOOST_CHECK(x == arr[i][j][k]);
                    ++k;
                }
                ++j;
            }
            ++i;
        }
    }
}


int test_main(int, char*[])
{
    ::test_2d();
    ::test_3d();
    return 0;
}
