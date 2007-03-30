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

        Derived& d = *this|static_downcasted;
        BOOST_CHECK( d.create_impl() == derived_create_value );
    }

    void show() const
    {
        // const-qualifier is optional here.
        BOOST_CHECK( pstade::static_downcast<Derived>(*this).show_impl() == derived_show_value );

        const Derived& d = *this|static_downcasted;
        BOOST_CHECK( d.show_impl() == derived_show_value );
    }

    void move()
    {
        Derived& d = *this|static_downcasted;
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


void test_cast()
{
    Base b;
    Derived& d = pstade::static_downcast<Derived>(b);
    std::cout << &d;
}


void test_auto()
{
    Base b;
    Derived& d = b|static_downcasted;
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
    Derived& d = b|static_downcasted;
    (void)d;
}


int test_main(int, char*[])
{
    ::test();
    ::test_cast();
    ::test_auto();
    return 0;
}
