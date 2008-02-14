#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/from.hpp>
#include <pstade/unit_test.hpp>


#include <boost/any.hpp>
#include <pstade/any.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/is_same.hpp>
#include <pstade/poly.hpp>


namespace egg = pstade::egg;
using namespace egg;


using pstade::any_ref;
using pstade::any_cref;
using pstade::any_movable;


struct my_base { virtual int value() const = 0; };
struct my_derived : my_base
{
    int m_value;

    explicit my_derived(int i) : m_value(i)
    {}

    int value() const { return m_value; }
};
struct my_derived2 : my_base
{
    int value() const { return 999; }
};


void test_from_any()
{

    {
        int i = 3;
        any_ref a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( is_same(*o, i) );

        // convertible type is no longer allowed.
        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( !co );

        {
            boost::optional<int &> o = X_from_any_to< boost::optional<int &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( is_same(*o, i) );

            // convertible type is no longer allowed.
            boost::optional<int const &> co = X_from_any_to< boost::optional<int const &> >()(a);
            BOOST_CHECK( !co );
        }

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

        {
            boost::optional<std::auto_ptr<int> &> o = X_from_any_to< boost::optional<std::auto_ptr<int> &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( **o == 9 );
            BOOST_CHECK( **o = 3 );
            BOOST_CHECK( **o == 3 );
        }


        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int i = 3;
        boost::any a = i;

        boost::optional<int &> o = from_boost_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( *o == i );

        boost::optional<int const &> co = from_boost_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == i );

        {
#if 0 // rejected
            boost::optional<int &> o = X_from_boost_any_to< boost::optional<int &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( *o == i );
#endif

            boost::optional<int const &> co = X_from_boost_any_to< boost::optional<int const &> >()(a);
            BOOST_CHECK( co );
            BOOST_CHECK( *co == i );
        }

#if 0 // rejected
        boost::optional<char &> q = from_boost_any(a);
        BOOST_CHECK( !q );
#endif
        boost::optional<char const &> cq = from_boost_any(a);
        BOOST_CHECK( !cq );
    }

    {
        int i = 3;
        boost::any const a = i;

        boost::optional<int const &> o = from_boost_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( *o == i );

        {
            boost::optional<int const &> co = X_from_boost_any_to< boost::optional<int const &> >()(a);
            BOOST_CHECK( co );
            BOOST_CHECK( *co == i );
        }

        boost::optional<char const &> cq = from_boost_any(a);
        BOOST_CHECK( !cq );
    }

#if 0 // rejected
    {
        int i = 3;
        boost::any const a = i;

        boost::optional<int &> o = from_boost_any(a);
        BOOST_CHECK( !o );
        {
            boost::optional<int &> o = X_from_boost_any_to< boost::optional<int &> >()(a);
            BOOST_CHECK( !o );
        }

        boost::optional<char &> q = from_boost_any(a);
        BOOST_CHECK( !q );
        boost::optional<char const &> cq = from_boost_any(a);
        BOOST_CHECK( !cq );
    }
#endif

    {
        using pstade::poly;
        
        my_derived i(3);
        poly<my_base> a = i;

        boost::optional<my_derived &> o = from_poly(a);
        BOOST_CHECK( o );
        BOOST_CHECK( o->value() == 3 );

        // convertible type is allowed.
        boost::optional<my_derived const &> co = from_poly(a);
        BOOST_CHECK( co );
        BOOST_CHECK( co->value() == 3 );

        {
            boost::optional<my_derived &> o = X_from_poly_to< boost::optional<my_derived &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( o->value() == 3 );

            // convertible type is allowed.
            boost::optional<my_derived const &> co = X_from_poly_to< boost::optional<my_derived const &> >()(a);
            BOOST_CHECK( co );
            BOOST_CHECK( co->value() == 3 );
        }

        boost::optional<my_derived2 &> q = from_poly(a);
        BOOST_CHECK( !q );
    }
    {// works as if boost::any.
        using pstade::poly;
        
        poly<void> a = 3;

        boost::optional<int &> o = from_poly(a);
        BOOST_CHECK( o );
        BOOST_CHECK( *o == 3 );

        // convertible type is allowed.
        boost::optional<int const &> co = from_poly(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == 3 );

        {
            boost::optional<int &> o = X_from_poly_to< boost::optional<int &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( *o == 3 );

            // convertible type is allowed.
            boost::optional<int const &> co = X_from_poly_to< boost::optional<int const &> >()(a);
            BOOST_CHECK( co );
            BOOST_CHECK( *co == 3 );
        }

        boost::optional<double &> q = from_poly(a);
        BOOST_CHECK( !q );
    }
}


void pstade_unit_test()
{
    test_from_any();
}
