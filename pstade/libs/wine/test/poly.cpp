#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// #define PSTADE_POLY_MIN_STORAGE_SIZE 2


#include <pstade/poly.hpp>


#if PSTADE_POLY_MIN_STORAGE_SIZE != 2 && \
    PSTADE_POLY_MIN_STORAGE_SIZE != 128 && \
    PSTADE_POLY_MIN_STORAGE_SIZE != 1024
#error unexpected testing value of PSTADE_POLY_MIN_STORAGE_SIZE
#endif


#include <pstade/unit_test.hpp>


#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/mpl/assert.hpp>
#include <string>
#include <boost/mpl/size_t.hpp>
#include <pstade/egg/do_swap.hpp>


using namespace pstade;


struct my_string_base
{
#if 0
    virtual ~my_string_base() {}
    virtual my_string_base *clone() const = 0;
#endif
    virtual std::string get_string() const = 0;

protected:
    ~my_string_base() { }
};

#if 0 // no longer needed
// Clonable implementation
my_string_base *new_clone(my_string_base const &s)
{
    return s.clone();
}
#endif

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
bool g_destructor_called;
struct my_stringH : my_string_base
{
    my_stringH(std::string s) : m_str(s)
    {
        index = 123;
        g_destructor_called = false;
    }

    std::string get_string() const // override
    {
        return m_str;
    }

    my_string_base *clone() const // override
    {
        return new my_stringH(m_str);
    }
    
    ~my_stringH()
    {
        g_destructor_called = true;
    }

    std::string m_str;
    double index;
    double dummy[30];
};


void pstade_unit_test()
{
    my_stringL sL;
    my_stringH sH("heap");

    {
        poly<int> p1;
        BOOST_CHECK( !p1 );
        poly<int> p2;
        BOOST_CHECK( !p2 );
        p1 = p2;
        BOOST_CHECK( !p1 );
        BOOST_CHECK( !p2 );
    }
    {// works as any (heap)
        poly<void> p(sH);
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<my_stringH>() );
        BOOST_CHECK( p.content<my_stringH>().index == 123 );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
    }
    {// works as any (local)
        poly<void> p(123);
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<int>() );
        BOOST_CHECK( p.content<int>() == 123 );
        BOOST_CHECK( p.type() == typeid(int) );
    }
    {// deleter check
        {
            poly<my_string_base> p(sH);
        }
        BOOST_CHECK(g_destructor_called);
        {
            poly<void> p(sH);
        }
        BOOST_CHECK(g_destructor_called);
    }
    {
        poly<my_string_base> p1(sL);
        poly<my_string_base> p2(sH);
        BOOST_CHECK( p1->get_string() == "local" );
        BOOST_CHECK( p2->get_string() == "heap" );
        pstade::egg::do_swap(p1, p2); // for now, not lightweight.
        BOOST_CHECK( p1->get_string() == "heap" );
        BOOST_CHECK( p2->get_string() == "local" );
        pstade::egg::do_swap(p1, p2); // for now, not lightweight.
        BOOST_CHECK( p1->get_string() == "local" );
        BOOST_CHECK( p2->get_string() == "heap" );
    }
    {
        BOOST_MPL_ASSERT((poly<int>::is_locally_stored<int>));
        poly<int> p(3);
        BOOST_CHECK( p );
        BOOST_CHECK( p.type() == typeid(int) );
        BOOST_CHECK( p.contains<int>() );
        BOOST_CHECK( p.content<int>() == 3 );
        p.reset();
        BOOST_CHECK(!p );
        //std::cout << p.type();
    }
    {
        BOOST_MPL_ASSERT((poly<my_string_base>::is_locally_stored<my_stringL>));
        poly<my_string_base> p(sL);
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<my_stringL>() );
        BOOST_CHECK( p.content<my_stringL>().get_string() == "local" );
        BOOST_CHECK( p.type() == typeid(my_stringL) );
        BOOST_CHECK( p->get_string() == "local" );
    }
    {
        poly<my_string_base> const p(sL);
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<my_stringL const>() );
        BOOST_CHECK( p.content<my_stringL const>().get_string() == "local" );
        BOOST_CHECK( p.type() == typeid(my_stringL) );
        BOOST_CHECK( p->get_string() == "local" );
    }
    {
#if PSTADE_POLY_MIN_STORAGE_SIZE != 1024
        BOOST_MPL_ASSERT_NOT((poly<my_string_base>::is_locally_stored<my_stringH>));
#else
        BOOST_MPL_ASSERT((poly<my_string_base>::is_locally_stored<my_stringH>));
#endif
        poly<my_string_base> p(sH);
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<my_stringH>() );
        BOOST_CHECK( p.content<my_stringH>().index == 123 );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );
    }
    {
        poly<my_string_base> const p(sH);
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<my_stringH const>() );
        BOOST_CHECK( p.content<my_stringH const>().index == 123 );
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
        BOOST_CHECK( p.contains<my_stringH>() );
        BOOST_CHECK( p.content<my_stringH>().index == 123 );
        BOOST_CHECK( p.type() == typeid(my_stringH) );
        BOOST_CHECK( p->get_string() == "heap" );
        p.reset();
        BOOST_CHECK(!p );
        p = sL;
        BOOST_CHECK( p );
        BOOST_CHECK( p.contains<my_stringL>() );
        BOOST_CHECK( p.content<my_stringL>().get_string() == "local" );
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
        
        // copy using reset
        poly<my_string_base> p4;
        p4.reset(p);
        BOOST_CHECK( p4 );
        BOOST_CHECK( p4.type() == typeid(my_stringH) );
        BOOST_CHECK( p4->get_string() == "heap" );
        p4.reset();
        BOOST_CHECK( !p4 );
    }
    {
        poly<my_string_base> p(sH);
        BOOST_CHECK( p == p );

        my_stringH sH2("heap");
        poly<my_string_base> p2(sH2);
        BOOST_CHECK( p == p2 ); // deep comparison

        poly<my_string_base> p3(sL);
        BOOST_CHECK( p != p3 );

        p.reset();
        BOOST_CHECK( p == p );
        BOOST_CHECK( p != p2 );

        poly<my_string_base> p4, p5;
        BOOST_CHECK( p4 == p5 );
        BOOST_CHECK( p4 != p3 );
    }
    {
        poly<int> p1(10);
        poly<int> p2(20);
        BOOST_CHECK( p1 < p2 ); // deep comparison
        BOOST_CHECK( p1 <= p2 );//
        BOOST_CHECK( p1 != p2 );//
    }
    {
    // poly-poly
        typedef poly<my_string_base> poly_string_base;
#if 0
        std::cout << poly_storage_size<my_string_base>::value << std::endl; // sizeof(my_string_base) * 2
        std::cout << poly_storage_size<poly_string_base>::value << std::endl; // sizeof(poly_strng_base) * 2
        std::cout << sizeof(my_string_base) << std::endl; // 4
        std::cout << sizeof(poly_string_base) << std::endl;  // 24
        std::cout << sizeof(poly<poly_string_base>) << std::endl; // 56
#endif

#if PSTADE_POLY_MIN_STORAGE_SIZE != 1024
        BOOST_MPL_ASSERT((poly<poly_string_base>::is_locally_stored<poly_string_base>));
#else
        // Both inner poly and outer poly reach to limit.
        BOOST_MPL_ASSERT_NOT((poly<poly_string_base>::is_locally_stored<poly_string_base>));
#endif
        poly_string_base p1(sL);
        poly<poly_string_base> p2(p1);
        BOOST_CHECK( (*p2)->get_string() == "local" );
    }
    {
#if PSTADE_POLY_MIN_STORAGE_SIZE == 128 // default case
        BOOST_STATIC_ASSERT((poly_storage_size<char>::value == PSTADE_POLY_MIN_STORAGE_SIZE));
        BOOST_STATIC_ASSERT((poly_storage_size<char[5000]>::value == PSTADE_POLY_MAX_STORAGE_SIZE));
        BOOST_STATIC_ASSERT((poly_storage_size<char[200]>::value == 400));
#endif
    }
}
