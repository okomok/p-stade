#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_cast.hpp>


#include <iostream>
#include <boost/noncopyable.hpp>
#include <pstade/unused.hpp>


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
        BOOST_CHECK( pstade::derived_cast<Derived>(*this).create_impl() == derived_create_value );

        Derived& d = pstade::derived(*this);
        BOOST_CHECK( d.create_impl() == derived_create_value );

    #if !defined(PSTADE_DERIVED_CAST_NO_POINTER_DERIVED)
        Derived *pd = pstade::derived(*this);
        BOOST_CHECK( pd->create_impl() == derived_create_value );
    #endif
    }

    void show() const
    {
        BOOST_CHECK( pstade::derived_cast<const Derived>(*this).show_impl() == derived_show_value );

        const Derived& d = pstade::derived(*this);
        BOOST_CHECK( d.show_impl() == derived_show_value );

    #if !defined(PSTADE_DERIVED_CAST_NO_POINTER_DERIVED)
        const Derived *pd = pstade::derived(*this);
        BOOST_CHECK( pd->show_impl() == derived_show_value );
    #endif
    }

    void move()
    {
        Derived& d = pstade::derived(*this);
        BOOST_CHECK( d.move_impl() == base_move_value );

    #if !defined(PSTADE_DERIVED_CAST_NO_POINTER_DERIVED)
        Derived *pd = pstade::derived(*this);
        BOOST_CHECK( pd->move_impl() == base_move_value );
    #endif
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


void test_cast()
{
    Base b;
    Derived& d = pstade::derived_cast<Derived>(b);
    std::cout << &d;
}


void test_auto()
{
    Base b;
    Derived& d = pstade::derived(b);
    std::cout << &d;
}


void test()
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
    Derived& d = b|pstade::to_derived;
    (void)d;
}


int test_main(int, char*[])
{
    ::test();
    ::test_cast();
    ::test_auto();
    return 0;
}
