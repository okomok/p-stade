#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/any.hpp>
#include <pstade/unit_test.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/is_same.hpp>


#include <pstade/egg/from_any_to.hpp>
#include <pstade/egg/do_swap.hpp>


using pstade::any_ref;
using pstade::any_cref;
using pstade::any_movable;
using pstade::egg::do_swap;
using pstade::egg::is_same;


void test_ref()
{
    {
        int i = 3;
        any_ref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.type() == typeid(boost::type<int>) );
        BOOST_CHECK( a.type() == typeid(boost::type<int>) );
        BOOST_CHECK( &(a.content<int>()) == &i );
        a.content< int >() = 6;
        BOOST_CHECK(i == 6);
        BOOST_CHECK( a.content< int >() == 6 );
        pstade::egg::any_to< int >(a) = 3;
        BOOST_CHECK( pstade::egg::any_to< int >(a) == 3 );
        a.type();

        a = boost::none;;
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK( a );
        BOOST_CHECK( &(a.content<int>()) == &i );
        a.content< int >() = 6;
        BOOST_CHECK(i == 6);

        BOOST_CHECK(a.contains<int>());

        // convertible type is no longer allowed.
        BOOST_CHECK(!a.contains<int const>());
    }
    {
        int i = 3, j = 5;
        any_ref a1(i);
        any_ref a2(j);
        do_swap(a1, a2);
        BOOST_CHECK( is_same(a1.content<int>(), j) );
        BOOST_CHECK( a1.content<int>() == 5 );
        BOOST_CHECK( is_same(a2.content<int>(), i) );
        BOOST_CHECK( a2.content<int>() == 3 );
    }
    {
        int const i = 3;
        any_ref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.content<int const>()) == &i );
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();

        BOOST_CHECK(!a.contains<int>());
        BOOST_CHECK(a.contains<int const>());
    }

    // const-ness doesn't affect.
    {
        int i = 3;
        any_ref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.type() == typeid(boost::type<int>) );
        a.content< int >() = 6;
        BOOST_CHECK( a.content< int >() == 6 );
        pstade::egg::any_to< int >(a) = 3;
        BOOST_CHECK( pstade::egg::any_to< int >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_ref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.type() == typeid(boost::type<int const>) );
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();
    }

    {
        int i = 3;
        any_ref a = i; // convertible
        BOOST_CHECK( a.content< int >() == 3 );
    }
    {
        int const i = 3;
        any_ref a = i; // convertible
        BOOST_CHECK( a.content< int const >() == 3 );
    }
    {
        int i = 3;
        any_ref const a(i);
        any_ref b(a); // direct
        BOOST_CHECK( a.content< int >() == 3 );
        BOOST_CHECK( b.content< int >() == 3 );
    }
    {
        int i = 3;
        any_ref a(i);
        any_ref b = a; // copy
        BOOST_CHECK( a.content< int >() == 3 );
        BOOST_CHECK( b.content< int >() == 3 );
    }
    {
        int i = 3;
        any_ref const a(i);
        any_ref b;
        b = a; // assign
        BOOST_CHECK( a.content< int >() == 3 );
        BOOST_CHECK( b.content< int >() == 3 );
    }
    {
        int const i = 3;
        any_ref a(i);
        any_ref b(a); // direct
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int const i = 3;
        any_ref const a(i);
        any_ref b = a; // copy
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int const i = 3;
        any_ref a(i);
        any_ref b;
        b = a; // assign
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int i = 3;
        any_ref a(i);
        any_ref b;
        b.reset(a);
        BOOST_CHECK( is_same(b.content<any_ref>().content<int>(), i) );
        a = boost::none;
        BOOST_CHECK( !a );
        BOOST_CHECK( !a.contains<int>() );
        BOOST_CHECK( b );
        BOOST_CHECK( b.contains< any_ref >() );
        b = boost::none;
        BOOST_CHECK( !b );
    }
    {
        int const i = 3;
        any_ref a(i);
        any_ref b;
        b.reset(a);
        BOOST_CHECK( is_same(b.content< any_ref >().content<int const>(), i) );
        a = boost::none;
        BOOST_CHECK( !a );
        BOOST_CHECK( !a.contains<int const>() );
        BOOST_CHECK( b );
        BOOST_CHECK( b.contains< any_ref >() );
        b = boost::none;
        BOOST_CHECK( !b );
    }
    {
        any_ref a;
        BOOST_CHECK(!a);
        BOOST_CHECK(a.empty());
        BOOST_CHECK(!a.contains<int>());
    }
    {
        int i = 3;
        char const j = 'a';
        any_ref a(i);
        any_ref b(j);
        pstade::egg::do_swap(a, b);
        BOOST_CHECK( is_same(a.content<char const>(), j) );
        BOOST_CHECK( is_same(b.content<int>(), i) );
    }
    { // using none
        int i = 3;
        any_ref a = boost::none;
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK(  a );
        a.reset(boost::none);
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK(  a );
        a = boost::none;
        BOOST_CHECK( !a );
    }
}

void test_cref()
{
    {
        int i = 3;
        any_cref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.type() == typeid(boost::type<int const>) );
        BOOST_CHECK( a.type() == typeid(boost::type<int const>) );
        BOOST_CHECK( &(a.content<int const>()) == &i );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();

        a = boost::none;
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK( a );
        BOOST_CHECK( &(a.content<int const>()) == &i );

        BOOST_CHECK(!a.contains<int>());
        BOOST_CHECK(a.contains<int const>());
    }
    {
        int i = 3, j = 5;
        any_cref a1(i);
        any_cref a2(j);
        do_swap(a1, a2);
        BOOST_CHECK( is_same(a1.content<int const>(), j) );
        BOOST_CHECK( a1.content<int const>() == 5 );
        BOOST_CHECK( is_same(a2.content<int const>(), i) );
        BOOST_CHECK( a2.content<int const>() == 3 );
    }
    {
        int i = 3;
        any_cref a;
        BOOST_CHECK( a.empty() );
        a = i;
        BOOST_CHECK( !a.empty() );

        // const is optional
        BOOST_CHECK( &(a.content<int const>()) == &i );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_cref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.content<int const>()) == &i );
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();
    }

    // const-ness doesn't affect.
    {
        int i = 3;
        any_cref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_cref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( pstade::egg::any_to< int const >(a) == 3 );
        a.type();
    }

    {
        int i = 3;
        any_cref a = i; // convertible
        BOOST_CHECK( a.content< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref a = i; // convertible
        BOOST_CHECK( a.content< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref const a(i);
        any_cref b(a); // direct
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref a(i);
        any_cref b = a; // copy
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref const a(i);
        any_cref b;
        b = a; // assign
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref a(i);
        any_cref b(a); // direct
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref const a(i);
        any_cref b = a; // copy
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref a(i);
        any_cref b;
        b = a; // assign
        BOOST_CHECK( a.content< int const >() == 3 );
        BOOST_CHECK( b.content< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref a(i);
        any_cref b;
        b.reset(a);
        BOOST_CHECK( is_same(b.content<any_cref const>(), a) );
        BOOST_CHECK( is_same(b.content<any_cref const>().content<int const>(), i) );
        a = boost::none;
        BOOST_CHECK( !a );
        BOOST_CHECK( !a.contains<int const>() );
        BOOST_CHECK( b );
        BOOST_CHECK( b.contains< any_cref const >() );
        b = boost::none;
        BOOST_CHECK( !b );
    }
    {
        any_cref a;
        BOOST_CHECK(!a);
        BOOST_CHECK(a.empty());
        BOOST_CHECK(!a.contains<int>());
    }
    {
        int i = 3;
        char const j = 'a';
        any_cref a(i);
        any_cref b(j);
        pstade::egg::do_swap(a, b);
        BOOST_CHECK( is_same(a.content<char const>(), j) );
        BOOST_CHECK( is_same(b.content<int const>(), i) );
    }
    { // using none
        int i = 3;
        any_cref a = boost::none;
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK(  a );
        a.reset(boost::none);
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK(  a );
        a = boost::none;
        BOOST_CHECK( !a );
    }
}


void test_movable()
{
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.type() == typeid(boost::type< std::auto_ptr<int> >) );
        BOOST_CHECK( a.type() == typeid(boost::type< std::auto_ptr<int> >) );
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
        BOOST_CHECK( *pstade::egg::any_to< std::auto_ptr<int> >(a) == 3 );
        a.type();

        std::auto_ptr<int> p(new int(3));
        a = boost::none;
        BOOST_CHECK( !a );
        a = p;
        BOOST_CHECK( a );
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
        BOOST_CHECK( *pstade::egg::any_to< std::auto_ptr<int> >(a) == 3 );

        BOOST_CHECK(a.contains< std::auto_ptr<int> >());

        // convertible type is no longer allowed.
        BOOST_CHECK(!a.contains< std::auto_ptr<int> const >());
    }
    {
        std::auto_ptr<int> i(std::auto_ptr<int>(new int(3))), j(std::auto_ptr<int>(new int(5)));
        any_movable a1(i);
        any_movable a2(j);
        do_swap(a1, a2);
        BOOST_CHECK( *a1.content< std::auto_ptr<int> >() == 5 );
        BOOST_CHECK( *a2.content< std::auto_ptr<int> >() == 3 );
    }
    {
        any_movable a = std::auto_ptr<int>(new int(3));
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a;
        BOOST_CHECK( a.empty() );
        a = any_movable(std::auto_ptr<int>(new int(3)));
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        std::auto_ptr<int> ap(a.content< std::auto_ptr<int> >());
        BOOST_CHECK( *ap == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        any_movable a_(a);
        BOOST_CHECK( *(a_.content< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        any_movable a_ = a;
        BOOST_CHECK( *(a_.content< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        any_movable a_; a_ = a;
        BOOST_CHECK( *(a_.content< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(9)));
        a = std::auto_ptr<int>(new int(3));
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a = std::auto_ptr<int>(new int(9)); // convertible
        a = std::auto_ptr<int>(new int(3)); // assignable
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
        std::auto_ptr<int> p = a.content< std::auto_ptr<int> >(); // movable
        BOOST_CHECK( *p == 3 );
    }
    { // const-ness doesn't affect
        any_movable const a = std::auto_ptr<int>(new int(3)); // convertible
        BOOST_CHECK( *(a.content< std::auto_ptr<int> >()) == 3 );
        std::auto_ptr<int> p = a.content< std::auto_ptr<int> >(); // movable
        BOOST_CHECK( *p == 3 );
    }
    {
        std::auto_ptr<int> i(new int(3));
        any_movable a(i);
        BOOST_CHECK( a.contains< std::auto_ptr<int> >() );
        any_movable b;
        b.reset(a);
        BOOST_CHECK( *b.content<any_movable>().content< std::auto_ptr<int> >() == *a.content< std::auto_ptr<int> >() );
        a = boost::none;
        BOOST_CHECK( !a );
        BOOST_CHECK( !a.contains< std::auto_ptr<int> >() );
        BOOST_CHECK( b );
        BOOST_CHECK( b.contains<any_movable>() );
        b = boost::none;
        BOOST_CHECK( !b );
    }
    {
        any_movable a;
        BOOST_CHECK(!a);
        BOOST_CHECK(a.empty());
        BOOST_CHECK(!a.contains<int>());
    }
    {
        std::auto_ptr<int> i(new int(3));
        std::auto_ptr<char> j(new char('a'));
        any_movable a(i);
        any_movable b(j);
        pstade::egg::do_swap(a, b);
        BOOST_CHECK( *a.content< std::auto_ptr<char> >() == 'a' );
        BOOST_CHECK( *b.content< std::auto_ptr<int> >() == 3 );
    }
    { // using none
        int i = 3;
        any_movable a = boost::none;
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK(  a );
        a.reset(boost::none);
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK(  a );
        a = boost::none;
        BOOST_CHECK( !a );
    }
}


void pstade_unit_test()
{
    test_ref();
    test_cref();
    test_movable();
}
