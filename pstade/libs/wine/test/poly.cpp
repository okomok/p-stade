#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/poly.hpp>
#include <pstade/unit_test.hpp>


#include <string>


using namespace pstade;


struct my_string_base
{
    virtual ~my_string_base() {}
    virtual std::string get_string() const = 0;
    virtual my_string_base *clone() const = 0;
};


// Clonable implementation
my_string_base *new_clone(my_string_base const &s)
{
    return s.clone();
}

bool operator==(my_string_base const &x, my_string_base const &y)
{
    return x.get_string() == y.get_string();
}


// local
struct my_stringL : my_string_base
{
    my_stringL() {}

    std::string get_string() const // override
    {
        return "local";
    }

    my_string_base *clone() const // override
    {
        return new my_stringL();
    }
};

// heap
struct my_stringH : my_string_base
{
    my_stringH(std::string s) : m_str(s) { index = 123; }

    std::string get_string() const // override
    {
        return m_str;
    }

    my_string_base *clone() const // override
    {
        return new my_stringH(m_str);
    }

    std::string m_str;
    double index;
    double d2;
    double d3;
    double d4;
    double d5;
};


void pstade_unit_test()
{
    my_stringL sL;
    my_stringH sH("heap");

    {
        poly<int> p(3);
        BOOST_CHECK( p );
        BOOST_CHECK( p.type() == typeid(int) );
        BOOST_CHECK( pstade::is_poly_castable_to<int>(p) );
        BOOST_CHECK( pstade::poly_cast<int>(p) == 3 );
        p.reset();
        BOOST_CHECK(!p );
        //std::cout << p.type();
    }
    {
        poly<my_string_base> p(sL);
        BOOST_CHECK( p );
        BOOST_CHECK( pstade::is_poly_castable_to<my_stringL>(p) );
        BOOST_CHECK( pstade::poly_cast<my_stringL>(p).get_string() == "local" );
        BOOST_CHECK( p.type() == typeid(my_stringL) );
        BOOST_CHECK( p->get_string() == "local" );
    }
    {
        poly<my_string_base> const p(sL);
        BOOST_CHECK( p );
        BOOST_CHECK( pstade::is_poly_castable_to<my_stringL const>(p) );
        BOOST_CHECK( pstade::poly_cast<my_stringL const>(p).get_string() == "local" );
        BOOST_CHECK( p.type() == typeid(my_stringL) );
        BOOST_CHECK( p->get_string() == "local" );
    }
    {
        poly<my_string_base> p(sH);
        BOOST_CHECK( p );
        BOOST_CHECK( pstade::is_poly_castable_to<my_stringH>(p) );
        BOOST_CHECK( pstade::poly_cast<my_stringH>(p).index == 123 );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );
    }
    {
        poly<my_string_base> const p(sH);
        BOOST_CHECK( p );
        BOOST_CHECK( pstade::is_poly_castable_to<my_stringH const>(p) );
        BOOST_CHECK( pstade::poly_cast<my_stringH const>(p).index == 123 );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );
    }
    {
        poly<my_string_base> p(sL);
        BOOST_CHECK( p );
        BOOST_CHECK( p.type() == typeid(my_stringL) );
        BOOST_CHECK( p->get_string() == "local" );
        p.reset();
        BOOST_CHECK(!p );
        p = sH;
        BOOST_CHECK( p );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );
        p.reset();
        BOOST_CHECK(!p );
        p.reset();
        BOOST_CHECK(!p );
    }
    {
        poly<my_string_base> p(sH);
        BOOST_CHECK( p );
        BOOST_CHECK( pstade::is_poly_castable_to<my_stringH>(p) );
        BOOST_CHECK( pstade::poly_cast<my_stringH>(p).index == 123 );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );
        p.reset();
        BOOST_CHECK(!p );
        p = sL;
        BOOST_CHECK( p );
        BOOST_CHECK( pstade::is_poly_castable_to<my_stringL>(p) );
        BOOST_CHECK( pstade::poly_cast<my_stringL>(p).get_string() == "local" );
        BOOST_CHECK( p.type() == typeid(my_stringL) );
        BOOST_CHECK( p->get_string() == "local" );
        p.reset();
        BOOST_CHECK(!p );
        p.reset();
        BOOST_CHECK(!p );
        BOOST_CHECK( p.type() == typeid(void) );

        p = sH;
        BOOST_CHECK( p );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );

        // assign to self
        p = p;
        BOOST_CHECK( p );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );

        // direct-init
        poly<my_string_base> p2(p);
        BOOST_CHECK( p2 );
        BOOST_CHECK( p2.type() == typeid(my_stringH) );
        BOOST_CHECK( p2->get_string() == "heap" );
        p2.reset();
        BOOST_CHECK( !p2 );

        // copy-init
        poly<my_string_base> p3 = p;
        BOOST_CHECK( p3 );
        BOOST_CHECK( p3.type() == typeid(my_stringH) );
        BOOST_CHECK( p3->get_string() == "heap" );
        p3.reset();
        BOOST_CHECK( !p3 );

        // assign to self
        p3 = p3;
        BOOST_CHECK( !p3 );
        BOOST_CHECK( p3.type() == typeid(void) );
    }
    {
        poly<my_string_base> p(sH);
        BOOST_CHECK( p == p );

        my_stringH sH2("heap");
        poly<my_string_base> p2(sH2);
        BOOST_CHECK( p == p2 ); // deep comarison

        poly<my_string_base> p3(sL);
        BOOST_CHECK( p != p3 );

        p.reset();
        BOOST_CHECK( p == p );
        BOOST_CHECK( p != p2 );

        poly<my_string_base> p4, p5;
        BOOST_CHECK( p4 == p5 );
        BOOST_CHECK( p4 != p3 );
    }
}
