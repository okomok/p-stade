#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_downcast.hpp>


#include <iostream>
#include <boost/noncopyable.hpp>
#include <pstade/unused.hpp>
#include <pstade/is_same.hpp>


using namespace pstade;


enum test_code
{
    derived_create_value,
    derived_show_value,
    base_move_value
};


template< class Derived >
struct WindowBase
{
    void create()
    {
        BOOST_CHECK( pstade::static_downcast<Derived>(*this).create_impl() == derived_create_value );

        Derived& d = pstade::static_downcast<Derived>(*this);
        BOOST_CHECK( d.create_impl() == derived_create_value );
    }

    void show() const
    {
        BOOST_CHECK( pstade::static_downcast<Derived>(*this).show_impl() == derived_show_value );

        const Derived& d = pstade::static_downcast<Derived>(*this);
        BOOST_CHECK( d.show_impl() == derived_show_value );
    }

    void move()
    {
        Derived& d = pstade::static_downcast<Derived>(*this);
        BOOST_CHECK( d.move_impl() == base_move_value );
    }

    test_code move_impl()
    {
        return base_move_value;
    }
};


struct Window : WindowBase< Window >, private boost::noncopyable
{
    test_code create_impl()
    {
        return derived_create_value;
    }

    test_code show_impl() const
    {
        return derived_show_value;
    }
};

struct Dialog : WindowBase< Dialog >
{
    Dialog(int)
    { }
    
    test_code create_impl()
    {
        return derived_create_value;
    }

    test_code show_impl() const
    {
        return derived_show_value;
    }
};


struct Base { };
struct Derived : Base { };


void test_crtp()
{
    Window wnd;
    wnd.create();
    wnd.show();
    wnd.move();

    Dialog dlg(1);
    dlg.create();
    dlg.show();
    dlg.move();

    Base b;
    Derived& d = pstade::static_downcast<Derived>(b);
    (void)d;
}


struct static_base_t : boost::noncopyable { };
struct static_derived_t : static_base_t { };

void test_static()
{
    static_derived_t D;
    static_base_t& rB = D;
    static_base_t const& crB = D;
    {
        static_derived_t& rD1 = pstade::static_downcast<static_derived_t>(rB);
        BOOST_CHECK( is_same(D, rD1) );
        static_derived_t& rD2 = pstade::static_downcast<static_derived_t&>(rB); // & is optional
        BOOST_CHECK( is_same(D, rD2) );

        static_derived_t const& crD1 = pstade::static_downcast<static_derived_t>(rB);
        BOOST_CHECK( is_same(D, crD1) );
        static_derived_t const& crD2 = pstade::static_downcast<static_derived_t const>(rB); // const is optional (of course)
        BOOST_CHECK( is_same(D, crD2) );
        static_derived_t const& crD3 = pstade::static_downcast<static_derived_t const&>(rB); // & is optional
        BOOST_CHECK( is_same(D, crD3) );
    }
    {
        static_derived_t const& crD1 = pstade::static_downcast<static_derived_t>(crB);
        BOOST_CHECK( is_same(D, crD1) );
        static_derived_t const& crD2 = pstade::static_downcast<static_derived_t const>(crB); // const is optional
        BOOST_CHECK( is_same(D, crD2) );
        static_derived_t const& crD3 = pstade::static_downcast<static_derived_t const&>(crB); // & is optional
        BOOST_CHECK( is_same(D, crD3) );
    }
}


struct polymorphic_base_t : boost::noncopyable { virtual ~polymorphic_base_t() { } };
struct polymorphic_derived_t : polymorphic_base_t { };
BOOST_MPL_ASSERT((boost::is_polymorphic<polymorphic_base_t>));

void test_polymorphic()
{
    polymorphic_derived_t D;
    polymorphic_base_t& rB = D;
    polymorphic_base_t const& crB = D;
    {
        polymorphic_derived_t& rD1 = pstade::static_downcast<polymorphic_derived_t>(rB);
        BOOST_CHECK( is_same(D, rD1) );
        polymorphic_derived_t& rD2 = pstade::static_downcast<polymorphic_derived_t&>(rB); // & is optional
        BOOST_CHECK( is_same(D, rD2) );

        polymorphic_derived_t const& crD1 = pstade::static_downcast<polymorphic_derived_t>(rB);
        BOOST_CHECK( is_same(D, crD1) );
        polymorphic_derived_t const& crD2 = pstade::static_downcast<polymorphic_derived_t const>(rB); // const is optional (of course)
        BOOST_CHECK( is_same(D, crD2) );
        polymorphic_derived_t const& crD3 = pstade::static_downcast<polymorphic_derived_t const&>(rB); // & is optional
        BOOST_CHECK( is_same(D, crD3) );
    }
    {
        polymorphic_derived_t const& crD1 = pstade::static_downcast<polymorphic_derived_t>(crB);
        BOOST_CHECK( is_same(D, crD1) );
        polymorphic_derived_t const& crD2 = pstade::static_downcast<polymorphic_derived_t const>(crB); // const is optional
        BOOST_CHECK( is_same(D, crD2) );
        polymorphic_derived_t const& crD3 = pstade::static_downcast<polymorphic_derived_t const&>(crB); // & is optional
        BOOST_CHECK( is_same(D, crD3) );
    }
}


int test_main(int, char*[])
{
    ::test_crtp();
    ::test_static();
    ::test_polymorphic();
    return 0;
}
