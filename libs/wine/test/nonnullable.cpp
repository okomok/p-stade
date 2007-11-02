#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/nonnullable.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/shared_ptr.hpp>
#include <boost/optional/optional.hpp>
#include <string>
#include <pstade/poly.hpp>
#include <pstade/egg/deref.hpp>


using pstade::nonnullable;


struct my_base
{
    virtual int hello() = 0;
};

struct my_derived : my_base
{
    virtual int hello() { return 10; }
};


void pstade_minimal_test()
{
    {
        nonnullable<int *> a(new int(3));
        BOOST_CHECK(a);
        BOOST_CHECK(*a == 3);
        delete &*a;
    }
    {
        nonnullable< boost::optional<int> > a(3);
        BOOST_CHECK(a);
        BOOST_CHECK(*a == 3);
        a.reset(4);
        BOOST_CHECK(*a == 4);
    }
    {// const doesn't affect in shared_ptr.
        nonnullable< boost::shared_ptr<int> > const a(new int(3));
        BOOST_CHECK(*a == 3);
        BOOST_CHECK(*a = 4);
        BOOST_CHECK(*a == 4);
    }
    {
        nonnullable< boost::shared_ptr<int> > a(new int(3));
        nonnullable< boost::shared_ptr<int> > b(new int(4));
        BOOST_CHECK(*a == 3);
        BOOST_CHECK(*b == 4);
        BOOST_CHECK(a != b);
        BOOST_CHECK(a < b);
        BOOST_CHECK(b > a);
        a.swap(b);
        BOOST_CHECK(*a == 4);
        BOOST_CHECK(*b == 3);
    }
    {
        nonnullable< boost::shared_ptr<int> > a(new int(3));
        nonnullable< boost::optional<int &> > b(*a);
        BOOST_CHECK(*a == *b);
        BOOST_CHECK(&*a == &*b);
    }
    {
        nonnullable< boost::shared_ptr<std::string> > a(new std::string("hello"));
        BOOST_CHECK(a->size() == 5);
    }
    {
        my_derived d;
        nonnullable< pstade::poly<my_base> > a(d);
        BOOST_CHECK( a.content().contains<my_derived>() );
        BOOST_CHECK(a->hello() == 10);
    }
    {
        my_derived d;
        nonnullable< pstade::poly<void> > a(d);
        BOOST_CHECK( a.content().contains<my_derived>() );
    }
    {
        nonnullable< boost::shared_ptr<int> > a(new int(3));
        BOOST_CHECK( pstade::egg::deref(a) == 3 );
    }
}
