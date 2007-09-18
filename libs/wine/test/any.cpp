#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/any.hpp>
#include <pstade/unit_test.hpp>


using pstade::any_ref;
using pstade::any_cref;
using pstade::any_movable;


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
        pstade::any_ref_cast< int >(a) = 3;
        BOOST_CHECK( pstade::any_ref_cast< int >(a) == 3 );
        a.type();

        a.reset();
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK( a );
        BOOST_CHECK( &(a.base<int>()) == &i );
        a.base< int >() = 6;
        BOOST_CHECK(i == 6);
    }
    {
        int const i = 3;
        any_ref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_ref_cast< int const >(a) == 3 );
        a.type();
    }

    // const-ness doesn't affect.
    {
        int i = 3;
        any_ref const a(i);
        BOOST_CHECK( !a.empty() );
        a.base< int >() = 6;
        BOOST_CHECK( a.base< int >() == 6 );
        pstade::any_ref_cast< int >(a) = 3;
        BOOST_CHECK( pstade::any_ref_cast< int >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_ref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_ref_cast< int const >(a) == 3 );
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
        BOOST_CHECK( &(a.base<int>()) == &i );
        BOOST_CHECK( pstade::any_cref_cast< int >(a) == 3 );
        a.type();

        a.reset();
        BOOST_CHECK( !a );
        a = i;
        BOOST_CHECK( a );
        BOOST_CHECK( &(a.base<int>()) == &i );
    }
    {
        int i = 3;
        any_cref a;
        BOOST_CHECK( a.empty() );
        a = i;
        BOOST_CHECK( !a.empty() );

        // const is optional
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( pstade::any_cref_cast< int const >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_cref a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( &(a.base<int const>()) == &i );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cref_cast< int const >(a) == 3 );
        a.type();
    }

    // const-ness doesn't affect.
    {
        int i = 3;
        any_cref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( pstade::any_cref_cast< int >(a) == 3 );
        a.type();
    }
    {
        int const i = 3;
        any_cref const a(i);
        BOOST_CHECK( !a.empty() );
        BOOST_CHECK( a.base< int const >() == 3 );
        BOOST_CHECK( pstade::any_cref_cast< int const >(a) == 3 );
        a.type();
    }

    {
        int i = 3;
        any_cref a = i; // convertible
        BOOST_CHECK( a.base< int >() == 3 );
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
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( b.base< int >() == 3 );
    }
    {
        int i = 3;
        any_cref a(i);
        any_cref b = a; // copy
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( b.base< int >() == 3 );
    }
    {
        int i = 3;
        any_cref const a(i);
        any_cref b;
        b = a; // assign
        BOOST_CHECK( a.base< int >() == 3 );
        BOOST_CHECK( b.base< int >() == 3 );
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
        BOOST_CHECK( *pstade::any_movable_cast< std::auto_ptr<int> >(a) == 3 );
        a.type();

        std::auto_ptr<int> p(new int(3));
        a.reset();
        BOOST_CHECK( !a );
        a = p;
        BOOST_CHECK( a );
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
        BOOST_CHECK( *pstade::any_movable_cast< std::auto_ptr<int> >(a) == 3 );
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
    { // const-ness doesn't affect
        any_movable const a = std::auto_ptr<int>(new int(3)); // convertible
        BOOST_CHECK( *(a.base< std::auto_ptr<int> >()) == 3 );
        std::auto_ptr<int> p = a.base< std::auto_ptr<int> >(); // movable
        BOOST_CHECK( *p == 3 );
    }
}


void pstade_unit_test()
{
    test_ref();
    test_cref();
    test_movable();
}
