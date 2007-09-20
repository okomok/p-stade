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


#include <boost/optional/optional.hpp>


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
        BOOST_CHECK( &(a.base<int>()) == &i );
        a.base< int >() = 6;
        BOOST_CHECK(i == 6);
        BOOST_CHECK( a.base< int >() == 6 );
        pstade::any_cast< int >(a) = 3;
        BOOST_CHECK( pstade::any_cast< int >(a) == 3 );
        a.type();

        a.reset();
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK( a );
        BOOST_CHECK( &(a.base<int>()) == &i );
        a.base< int >() = 6;
        BOOST_CHECK(i == 6);

        BOOST_CHECK(a.is_castable_to<int>());
        BOOST_CHECK(a.is_castable_to<int const>());
        BOOST_CHECK( is_same(a.base<int const>(), i) );
    }
    {
        int i = 3, j = 5;
        any_ref a1(i);
        any_ref a2(j);
        do_swap(a1, a2);
        BOOST_CHECK( is_same(a1.base<int>(), j) );
        BOOST_CHECK( a1.base<int>() == 5 );
        BOOST_CHECK( is_same(a2.base<int>(), i) );
        BOOST_CHECK( a2.base<int>() == 3 );
    }
    {
        int const i = 3;
        any_ref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();

        BOOST_CHECK(!a.is_castable_to<int>());
        BOOST_CHECK(a.is_castable_to<int const>());
    }

    // const-ness doesn't affect.
    {
        int i = 3;
        any_ref const a(i);
        BOOST_CHECK( !a.empty() );
        a.base< int >() = 6;
        BOOST_CHECK( a.base< int >() == 6 );
        pstade::any_cast< int >(a) = 3;
        BOOST_CHECK( pstade::any_cast< int >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_ref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();
    }

    {
        int i = 3;
        any_ref a = i; // convertible
        BOOST_CHECK( a.base< int >() == 3 );
    }
    {
        int const i = 3;
        any_ref a = i; // convertible
        BOOST_CHECK( a.base< int const >() == 3 );
    }
    {
        int i = 3;
        any_ref const a(i);
        any_ref b(a); // direct
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( b.base< int >() == 3 );
    }
    {
        int i = 3;
        any_ref a(i);
        any_ref b = a; // copy
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( b.base< int >() == 3 );
    }
    {
        int i = 3;
        any_ref const a(i);
        any_ref b;
        b = a; // assign
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( b.base< int >() == 3 );
    }
    {
        int const i = 3;
        any_ref a(i);
        any_ref b(a); // direct
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int const i = 3;
        any_ref const a(i);
        any_ref b = a; // copy
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int const i = 3;
        any_ref a(i);
        any_ref b;
        b = a; // assign
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
}

void test_cref()
{
    {
        int i = 3;
        any_cref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();

        a.reset();
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK( a );
        BOOST_CHECK( &(a.base<int const>()) == &i );

        BOOST_CHECK(!a.is_castable_to<int>());
        BOOST_CHECK(a.is_castable_to<int const>());
    }
    {
        int i = 3, j = 5;
        any_cref a1(i);
        any_cref a2(j);
        do_swap(a1, a2);
        BOOST_CHECK( is_same(a1.base<int const>(), j) );
        BOOST_CHECK( a1.base<int const>() == 5 );
        BOOST_CHECK( is_same(a2.base<int const>(), i) );
        BOOST_CHECK( a2.base<int const>() == 3 );
    }
    {
        int i = 3;
        any_cref a;
        BOOST_CHECK( a.empty() );
        a = i;
        BOOST_CHECK( !a.empty() );

        // const is optional
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_cref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();
    }

    // const-ness doesn't affect.
    {
        int i = 3;
        any_cref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_cref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cast< int const >(a) == 3 );
        a.type();
    }

    {
        int i = 3;
        any_cref a = i; // convertible
        BOOST_CHECK( a.base< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref a = i; // convertible
        BOOST_CHECK( a.base< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref const a(i);
        any_cref b(a); // direct
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref a(i);
        any_cref b = a; // copy
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int i = 3;
        any_cref const a(i);
        any_cref b;
        b = a; // assign
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref a(i);
        any_cref b(a); // direct
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref const a(i);
        any_cref b = a; // copy
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
    {
        int const i = 3;
        any_cref a(i);
        any_cref b;
        b = a; // assign
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( b.base< int const >() == 3 );
    }
}


void test_movable()
{
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
        BOOST_CHECK( *pstade::any_cast< std::auto_ptr<int> >(a) == 3 );
        a.type();

        std::auto_ptr<int> p(new int(3));
        a.reset();
        BOOST_CHECK( !a );
        a = p;
        BOOST_CHECK( a );
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
        BOOST_CHECK( *pstade::any_cast< std::auto_ptr<int> >(a) == 3 );

        BOOST_CHECK(a.is_castable_to< std::auto_ptr<int> >());
        BOOST_CHECK(a.is_castable_to< std::auto_ptr<int> const >());
    }
    {
        std::auto_ptr<int> i(std::auto_ptr<int>(new int(3))), j(std::auto_ptr<int>(new int(5)));
        any_movable a1(i);
        any_movable a2(j);
        do_swap(a1, a2);
        BOOST_CHECK( *a1.base< std::auto_ptr<int> >() == 5 );
        BOOST_CHECK( *a2.base< std::auto_ptr<int> >() == 3 );
    }
    {
        any_movable a = std::auto_ptr<int>(new int(3));
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a;
        BOOST_CHECK( a.empty() );
        a = any_movable(std::auto_ptr<int>(new int(3)));
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        std::auto_ptr<int> ap(a.base< std::auto_ptr<int> >());
        BOOST_CHECK( *ap == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        any_movable a_(a);
        BOOST_CHECK( *(a_.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        any_movable a_ = a;
        BOOST_CHECK( *(a_.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(3)));
        any_movable a_; a_ = a;
        BOOST_CHECK( *(a_.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a(std::auto_ptr<int>(new int(9)));
        a = std::auto_ptr<int>(new int(3));
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable a = std::auto_ptr<int>(new int(9)); // convertible
        a = std::auto_ptr<int>(new int(3)); // assignable
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
        std::auto_ptr<int> p = a.base< std::auto_ptr<int> >(); // movable
        BOOST_CHECK( *p == 3 );
    }
    {
        any_movable a = std::auto_ptr<int>(new int(9)); // convertible
        a = std::auto_ptr<int>(new int(3)); // assignable
        BOOST_CHECK( *(a.base< std::auto_ptr<int> const >()) == 3 );
        std::auto_ptr<int> p = a.base< std::auto_ptr<int> >(); // movable
        BOOST_CHECK( *p == 3 );
    }
    { // const-ness doesn't affect
        any_movable const a = std::auto_ptr<int>(new int(3)); // convertible
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
        std::auto_ptr<int> p = a.base< std::auto_ptr<int> >(); // movable
        BOOST_CHECK( *p == 3 );
    }
}


void test_from_any()
{
    using pstade::from_any;

    {
        int i = 3;
        any_ref a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( is_same(*o, i) );

        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( is_same(*co, i) );

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int const i = 3;
        any_ref a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( !o );

#if !defined(__GNUC__)
        // for some reason, copy-initialization doesn't work.
        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == 3 );
        BOOST_CHECK( is_same(*co, i) );
#endif 

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int const i = 3;
        any_cref a = i;

#if !defined(__GNUC__)
        // for some reason, copy-initialization doesn't work.
        boost::optional<int const &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( is_same(*o, i) );
#endif

        boost::optional<int &> q = from_any(a);
        BOOST_CHECK( !q );
        
        boost::optional<char &> q_ = from_any(a);
        BOOST_CHECK( !q_ );
    }
    {
        std::auto_ptr<int> i(new int(3));
        any_movable a = i;

        boost::optional<std::auto_ptr<int> &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( **o == 3 );
        BOOST_CHECK( **o = 9 );
        BOOST_CHECK( **o == 9 );

        boost::optional<std::auto_ptr<int> const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( **co == 9);

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int i = 3;
        boost::any a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( *o == i );

        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == i );

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
        boost::optional<char const &> cq = from_any(a);
        BOOST_CHECK( !cq );
    }
    {
        int i = 3;
        boost::any const a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( !o );

        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == i );

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
        boost::optional<char const &> cq = from_any(a);
        BOOST_CHECK( !cq );
    }
}


void test_any_cast()
{
    {
        int i = 10;
        boost::any a(i);

        int & i_ = pstade::any_cast<int>(a);
        BOOST_CHECK(i_ == 10);
    }
    {
        int i = 10;
        boost::any const a(i);

        int const & i_ = pstade::any_cast<int const>(a);
        BOOST_CHECK(i_ == 10);
    }
}


void pstade_unit_test()
{
    test_ref();
    test_cref();
    test_movable();
    test_from_any();
    test_any_cast();
}
