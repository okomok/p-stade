#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/value_based.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/shared_ptr.hpp>
#include <string>
#include <pstade/clone_ptr.hpp>
#include <pstade/egg/deref.hpp>


using pstade::value_based;


template<class IntPtr, class StringPtr>
void test_ptr()
{
    {
        value_based< IntPtr > v;
        BOOST_CHECK(!v);

        v = 10;
        BOOST_CHECK(v);
        BOOST_CHECK( *v == 10 );

        v = boost::none;
        BOOST_CHECK(!v);

        v.reset(10);
        BOOST_CHECK(v);
        BOOST_CHECK( *v == 10 );

        v = v;
        BOOST_CHECK(v);
        BOOST_CHECK( *v == 10 );
    }
    {
        value_based< IntPtr > v(10);
        BOOST_CHECK(v);
        BOOST_CHECK( *v == 10 );
    }
    {
        value_based< StringPtr > v = std::string("abcdef");
        BOOST_CHECK(v);
        BOOST_CHECK( !v->empty() );
        BOOST_CHECK( *v == std::string("abcdef") );
    }
    {
        value_based< IntPtr > v = boost::none;
        BOOST_CHECK(!v);
    }
    {
        value_based< IntPtr > v1, v2;
        BOOST_CHECK(!v1);
        BOOST_CHECK(!v2);

        v1 = v2;
        BOOST_CHECK(!v1);
        BOOST_CHECK(!v2);

        v2 = v1;
        BOOST_CHECK(!v1);
        BOOST_CHECK(!v2);
    }
    {
        value_based< IntPtr > v1(10), v2;
        BOOST_CHECK( v1);
        BOOST_CHECK( *v1 == 10 );
        BOOST_CHECK(!v2);

        v2 = v1;
        BOOST_CHECK( v1);
        BOOST_CHECK( v2);
        BOOST_CHECK( *v1 == 10 );
        BOOST_CHECK( *v2 == 10 );
        BOOST_CHECK( v1 == v2 );
    }
    {
        value_based< IntPtr > v(10);
        BOOST_CHECK(v);
        BOOST_CHECK( *v == 10 );
    }
    {
        value_based< IntPtr > v1(10), v2(20);
        BOOST_CHECK( v1 < v2 );
        v1.swap(v2);
        BOOST_CHECK( *v1 == 20 );
        BOOST_CHECK( *v2 == 10 );
        BOOST_CHECK( v2 < v1 );
    }
    {
        pstade::value_based< IntPtr > v(3);
        BOOST_CHECK( pstade::egg::deref(v) == 3 );
        BOOST_CHECK( pstade::egg::deref(v) = 4 );
        BOOST_CHECK( pstade::egg::deref(v) == 4 );
    }
    {
        pstade::value_based< IntPtr > const v(3);
        BOOST_CHECK( pstade::egg::deref(v) == 3 );
    }
}


struct my_B { virtual ~my_B() {} };
struct my_D : my_B {};

void test_conv()
{
    {
        value_based< boost::shared_ptr<my_B> > v = my_D();
        BOOST_CHECK(v);
    }
    {
        value_based< pstade::clone_ptr<my_B> > v = my_D();
        BOOST_CHECK(v);
    }
}


void pstade_minimal_test()
{
    ::test_ptr< boost::shared_ptr<int>, boost::shared_ptr<std::string> >();
    ::test_ptr< pstade::clone_ptr<int>, pstade::clone_ptr<std::string> >();
    ::test_conv();
}
