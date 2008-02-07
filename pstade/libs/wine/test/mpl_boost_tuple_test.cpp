
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date: 2004-09-03 00:41:37 +0900 (Fri, 03 Sep 2004) $
// $Revision: 24874 $

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>

#include <boost/mpl/aux_/test.hpp>

#include <pstade/mpl_boost_tuple.hpp>


MPL_TEST_CASE()
{
    typedef boost::tuples::tuple<> l0;
    typedef boost::tuples::tuple<char> l1;
    typedef boost::tuples::tuple<char,long> l2;
    typedef boost::tuples::tuple<char,char,char,char,char,char,char,char,char> l9;

    MPL_ASSERT_RELATION(size<l0>::value, ==, 0);
    MPL_ASSERT_RELATION(size<l1>::value, ==, 1);
    MPL_ASSERT_RELATION(size<l2>::value, ==, 2);
    MPL_ASSERT_RELATION(size<l9>::value, ==, 9);

    MPL_ASSERT(( empty<l0> ));
    MPL_ASSERT_NOT(( empty<l1> ));
    MPL_ASSERT_NOT(( empty<l2> ));
    MPL_ASSERT_NOT(( empty<l9> ));

    MPL_ASSERT(( is_same<front<l1>::type,char> ));
    MPL_ASSERT(( is_same<front<l2>::type,char> ));
    MPL_ASSERT(( is_same<front<l9>::type,char> ));
}

MPL_TEST_CASE()
{
    typedef boost::tuples::tuple<char,long> l2;
    
    typedef begin<l2>::type i1;
    typedef next<i1>::type  i2;
    typedef next<i2>::type  i3;
    
    MPL_ASSERT(( is_same<deref<i1>::type,char> ));
    MPL_ASSERT(( is_same<deref<i2>::type,long> ));
    MPL_ASSERT(( is_same< i3, end<l2>::type > ));
}

MPL_TEST_CASE()
{
    typedef boost::tuples::tuple<> l0;

    typedef push_front<l0,char>::type l1;
    MPL_ASSERT(( is_same<front<l1>::type,char> ));

    typedef push_front<l1,long>::type l2;
    MPL_ASSERT(( is_same<front<l2>::type,long> ));
}
