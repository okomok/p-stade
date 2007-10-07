#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <pstade/minimal_test.hpp>


#include <string>


void pstade_minimal_test()
{
    {
        int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
        boost::range_reverse_iterator<int[10]>::type r = boost::rbegin(a);
        BOOST_CHECK( *r == 9 );
        *r = 8;
        BOOST_CHECK( a[9] == 8 );
        *boost::rbegin(a) = 7;
        BOOST_CHECK( a[9] == 7 );
    }
    {
        int const a[10] = { 0,1,2,3,4,5,6,7,8,9 };
        boost::range_reverse_iterator<int const[10]>::type r = boost::rbegin(a);
        BOOST_CHECK( *r == 9 );
    }
    {
        std::string a("0123456789");
        boost::range_reverse_iterator<std::string>::type r = boost::rbegin(a);
        BOOST_CHECK( *r == '9' );
        *boost::rbegin(a) = '7';
        BOOST_CHECK( a[9] == '7' );
    }
    {
        std::string const a("0123456789");
        boost::range_reverse_iterator<std::string const>::type r = boost::rbegin(a);
        BOOST_CHECK( *r == '9' );
    }
}
