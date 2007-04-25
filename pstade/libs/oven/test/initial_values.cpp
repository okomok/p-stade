#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/initial_values.hpp>


#include <vector>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copy_range.hpp>
#include <boost/range/empty.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/copy_assign.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/used.hpp>
#include <boost/array.hpp>
#include <boost/implicit_cast.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct array_init
{
    // 'boost::array' is Aggregate, hence direct-initialization is always ok.
    array_init() :
        m_arr(initial_values(1,2,3,4,5))
    {
        int const ans[5] = { 1,2,3,4,5 };
        BOOST_CHECK(equals(m_arr, ans));
    }

private:
    boost::array<int, 5> m_arr;
};


void test()
{
    {
        ::array_init arr_init_test;
    }
    {// which is faster? (under VC8)
        boost::array<int, 4> arr(initial_values(1,2,3,4));
        /*
	        mov	ebp, 1
	        lea	ecx, DWORD PTR [ebp+1]
	        lea	eax, DWORD PTR [ebp+2]
	        lea	edx, DWORD PTR [ebp+3]
	        mov	DWORD PTR _arr$202789[esp+772], eax
	        mov	DWORD PTR _arr$202789[esp+776], edx

	        lea	esi, DWORD PTR _arr$202789[esp+764]
	        mov	DWORD PTR _arr$202789[esp+768], ecx
	        mov	BYTE PTR $T424376[esp+764], 0
	        mov	DWORD PTR _arr$202789[esp+764], ebp

	        mov	DWORD PTR _p$424394[esp+764], esi
        */

        // boost::array<int, 4> arr = { { 1,2,3,4 } };
        /*
	        mov	ebp, 1
	        mov	ecx, 2
	        mov	eax, 3
	        mov	edx, 4
	        mov	DWORD PTR _arr$202739[esp+764], eax
	        mov	DWORD PTR _arr$202739[esp+768], edx

	        lea	esi, DWORD PTR _arr$202739[esp+756]
	        mov	DWORD PTR _arr$202739[esp+760], ecx
	        mov	DWORD PTR _arr$202739[esp+756], ebp

	        mov	DWORD PTR _p$424103[esp+756], esi
        */

        pstade::used(arr);
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> vec = initial_values(1,5,3,6,1,3,7,1,4,2,2);
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[11] = { 1,5,3,6,1,3,7,1,4,2,2 };
        boost::array<int, 11> vec = initial_values(1,5,3,6,1,3,7,1,4,2,2);
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> vec;
        pstade::copy_assign(vec, initial_values(1,5,3,6,1,3,7,1,4,2,2));
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> vec(oven::copy_range< std::vector<int> >(initial_values(1,5,3,6,1,3,7,1,4,2,2)));
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[11] = { 1,5,3,6,1,3,7,1,4,2,2 };
        boost::array<int, 11> vec = initial_values(1,5,3,6,1,3,7,1,4,2,2)|copied;
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            initial_values(1,5,3,6,1,3,7,1,4,2,2),
            expected
        ) );
    }
#if 0 // rejected; nullary cannot be a range.
    {
        std::vector<int> vec = initial_values();
        BOOST_CHECK( boost::empty(vec) );
    }
#endif
    {
        boost::result_of<op_initial_values<>(int,int,int)>::type result = { { 1,2,3 } };
        // boost::result_of<op_initial_values<>()>::type nullary_result = { };
        pstade::unused(result); //, nullary_result);
    }
    {
        typedef std::vector<int>  row;
        typedef std::vector<row>  matrix;

        matrix m = initial_values(
            initial_values(1,2,3),
            initial_values(4,5,6),
            initial_values(7,8,9)
        );

        BOOST_CHECK( m[1][2] == 6 );
    }
    {
        typedef std::vector<int>  row;
        typedef std::vector<row>  matrix;

        matrix m = initial_values(
            // 2nd and 3rd must be convertible to 1st,
            // hence their arity must be smaller than 1st's.
            initial_values(1,2,3), // 1st
            initial_values(4,5), // 2nd
            initial_values(7)  // 3rd
        );

        BOOST_CHECK( m[2][0] == 7 );
    }
    {
        typedef std::vector<int>  row;
        typedef std::vector<row>  matrix;

        matrix m = initial_values(
            // row(initial_values(1,2,3)), // direct-initialization may fail. (GCC actually fails.)
            boost::implicit_cast<row>(initial_values(1,2,3)), // force copy-initialization.
            initial_values(4,5),
            initial_values(7)
        );

        BOOST_CHECK( m[1][0] == 4 );
    }
    { // explicit call
        typedef std::vector<int>  row;
        typedef std::vector<row>  matrix;

        matrix m = op_initial_values<row>()(
            initial_values(1,2,3),
            initial_values(4,5),
            initial_values(7)
        );

        BOOST_CHECK( m[1][0] == 4 );
    }
    {
        int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
        std::vector<int> vec = initial_values(1,5,3,6,1)|jointed(initial_values(3,7,1,4,2,2))|copied;
        BOOST_CHECK( equals(vec, ans) );
    }
    {
        std::vector<int> vec = initial_values(1,2,3,4,5);
        BOOST_CHECK( equals(
            vec,
            boost::implicit_cast< std::vector<int> >(initial_values(1,2,3,4,5))
        ) );

        pstade::copy_assign(vec, initial_values(1,2,3,4,5));
    }
    {
        std::vector<int> vec = initial_values(1,2,3,4,5);
        BOOST_CHECK( equals(
            boost::implicit_cast< std::vector<int> >(initial_values(1,2,3,4,5)),
            pstade::copy_construct< std::vector<int> >(initial_values(1,2,3,4,5))
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
