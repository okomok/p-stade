#ifndef PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP
#define PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Based on Eric Niebler's example.


#include <boost/egg/indirect.hpp>
#include <boost/egg/function.hpp>
#include <boost/egg/uncurry.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/ambi.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/construct.hpp>


struct little_my_id
{
    template<class Me, class X>
    struct apply
    {
        typedef X &type;
    };

    template<class Re, class X>
    Re call(X &x) const
    {
        return x;
    }

    int base() const { return touch; }

    int touch;
};


// Note that if the ODR violation baster:
//   http://lists.boost.org/Archives/boost/2007/06/123353.php
// is applied to these pod constants, gcc can't static-initialize my_idr;
// An address expression &my_id isn't statically placed in my_idr.


typedef boost::egg::function<little_my_id> T_my_id;
BOOST_EGG_CONST((T_my_id), my_id)
    = {{999}};

T_my_id const &get_my_id1();
T_my_id const &get_my_id2();


typedef boost::egg::result_of_indirect<T_my_id const *>::type T_my_idr;
BOOST_EGG_CONST((T_my_idr), my_idr)
    = BOOST_EGG_INDIRECT_L &my_id BOOST_EGG_INDIRECT_R;

T_my_idr const &get_my_idr1();
T_my_idr const &get_my_idr2();



struct my_little
{
    template<class Me, class A1, class A2, class A3, class A4>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Re, class A1, class A2, class A3, class A4>
    Re call(A1 &a1, A2 &, A3 &, A4 &) const
    {
        return a1;
    }

    int base() const { return touch; }

    int touch;
};

typedef
    boost::egg::function<my_little>
T_my_func_;

typedef
    boost::egg::result_of_uncurry<
        boost::egg::result_of_curry4<T_my_func_>::type
    >::type
T_my_func;
BOOST_EGG_CONST((T_my_func), my_func) = BOOST_EGG_UNCURRY_L BOOST_EGG_CURRY4_L {{999}} BOOST_EGG_CURRY4_R BOOST_EGG_UNCURRY_R;

T_my_func const &get_my_func1();
T_my_func const &get_my_func2();


typedef boost::egg::result_of_indirect<T_my_idr const *>::type T_my_idrr;
BOOST_EGG_CONST((T_my_idrr), my_idrr)
    = BOOST_EGG_INDIRECT_L &my_idr BOOST_EGG_INDIRECT_R;

T_my_idrr const &get_my_idrr1();
T_my_idrr const &get_my_idrr2();


struct T_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }

    int base() const { return touch; }

    int touch;
};

typedef boost::egg::result_of_pipable<T_my_plus>::type T_pipa;
BOOST_EGG_CONST((T_pipa), pipa) = BOOST_EGG_PIPABLE_L {999} BOOST_EGG_PIPABLE_R;
T_pipa const &get_pipa1();
T_pipa const &get_pipa2();

typedef boost::egg::result_of_ambi1<T_my_plus>::type T_auxi;
BOOST_EGG_CONST((T_auxi), auxi) = BOOST_EGG_AMBI_L {999} BOOST_EGG_AMBI_R;
T_auxi const &get_auxi1();
T_auxi const &get_auxi2();


typedef boost::egg::static_<boost::egg::X_construct<int, boost::egg::mpl_1> >::type T_construct_int;
T_construct_int const construct_int = BOOST_EGG_STATIC();
T_construct_int const &get_cons_int1();
T_construct_int const &get_cons_int2();


#endif
