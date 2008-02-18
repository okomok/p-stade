

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_facade.hpp>
#include "./egg_test.hpp"


#include <memory> // auto_ptr
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/test.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_ref.hpp>


using namespace pstade::egg;


struct my_value_identity :
    function_facade<my_value_identity, by_value>
{
    template<class Me, class X>
    struct apply
    {
        BOOST_MPL_ASSERT_NOT((boost::is_const<X>));
        BOOST_MPL_ASSERT_NOT((boost::is_reference<X>));
        typedef X type;
    };

    template<class Re, class X>
    Re call(X x) const
    {
        return x;
    }
};


struct my_cref_identity :
    function_facade<my_cref_identity, by_cref>
{
    template<class Me, class X>
    struct apply
    {
        BOOST_MPL_ASSERT((boost::is_const<X>));
        BOOST_MPL_ASSERT_NOT((boost::is_reference<X>));
        typedef X& type;
    };

    template<class Re, class X>
    Re call(X& x) const
    {
        return x;
    }
};


struct my_ref_identity :
    function_facade<my_ref_identity, by_ref>
{
    template<class Me, class X>
    struct apply
    {
        typedef X& type;
    };

    template<class Re, class X>
    Re call(X& x) const
    {
        return x;
    }
};



struct my_value_big_arity :
    function_facade<my_value_big_arity, by_value>
{
    template<class Me, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {
        typedef A0 type;
    };

    template<class Re, class A0>
    Re call(A0 a0, ...) const
    {
        return a0;
    }
};


struct my_cref_big_arity :
    function_facade<my_cref_big_arity, by_cref>
{
    template<class Me, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {
        typedef A0& type;
    };

    template<class Re, class A0>
    Re call(A0& a0, ...) const
    {
        return a0;
    }
};



struct my_ref_big_arity :
    function_facade<my_ref_big_arity, by_ref>
{
    template<class Me, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {
        typedef A0& type;
    };

    template<class Re, class A0>
    Re call(A0& a0, ...) const
    {
        return a0;
    }
};


void egg_test()
{
    {
        std::auto_ptr<int> ap = my_value_identity()( std::auto_ptr<int>(new int(3)) );
        BOOST_CHECK( *ap == 3 );
    }
    {
        int const i = 3;
        BOOST_CHECK( &(my_cref_identity()(i)) == &i );
        BOOST_CHECK( my_cref_identity()(3) == 3 );
    }
    {
        int const i = 3;
        BOOST_CHECK( &(my_ref_identity()(i)) == &i );
    }

    {
        std::auto_ptr<int> ap = my_value_big_arity()( std::auto_ptr<int>(new int(3)), 1,2,3,4,5,6,7,8,9);
        BOOST_CHECK( *ap == 3 );
    }
    {
        int const i = 3;
        BOOST_CHECK( &(my_cref_big_arity()(i,1,2,3,4,5,6,7,8,9)) == &i );
        BOOST_CHECK( my_cref_big_arity()(3,1,2,3,4,5,6,7,8,9) == 3 );
    }
    {
        int const i1 = 1, i2 = 2, i3 = 3, i4 = 4;
        int i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;
        std::auto_ptr<int> ap_(new int(3));
        std::auto_ptr<int> ap = my_ref_big_arity()(ap_, i1,i2,i3,i4,i5,i6,i7,i8,i9);
        BOOST_CHECK( *ap == 3 );
    }
}
