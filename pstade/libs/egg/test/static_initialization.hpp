#ifndef PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP
#define PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Based on Eric Niebler's example.


#include <pstade/egg/indirect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/uncurry.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/egg/static.hpp>
#include <pstade/egg/construct.hpp>


struct little_my_id
{
    template<class Myself, class X>
    struct apply
    {
        typedef X &type;
    };

    template<class Result, class X>
    Result call(X &x) const
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


typedef pstade::egg::function<little_my_id> T_my_id;
PSTADE_POD_CONSTANT((T_my_id), my_id)
    = {{999}};

T_my_id const &get_my_id1();
T_my_id const &get_my_id2();


typedef pstade::egg::result_of_indirect<T_my_id const *>::type T_my_idr;
PSTADE_POD_CONSTANT((T_my_idr), my_idr)
    = PSTADE_EGG_INDIRECT_L &my_id PSTADE_EGG_INDIRECT_R;

T_my_idr const &get_my_idr1();
T_my_idr const &get_my_idr2();



struct my_little
{
    template<class Myself, class A1, class A2, class A3, class A4>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Result, class A1, class A2, class A3, class A4>
    Result call(A1 &a1, A2 &, A3 &, A4 &) const
    {
        return a1;
    }

    int base() const { return touch; }

    int touch;
};

typedef
    pstade::egg::function<my_little>
T_my_func_;

typedef
    pstade::egg::result_of_uncurry<
        pstade::egg::result_of_curry4<T_my_func_>::type
    >::type
T_my_func;
PSTADE_POD_CONSTANT((T_my_func), my_func) = PSTADE_EGG_UNCURRY_L PSTADE_EGG_CURRY4_L {{999}} PSTADE_EGG_CURRY4_R PSTADE_EGG_UNCURRY_R;

T_my_func const &get_my_func1();
T_my_func const &get_my_func2();


typedef pstade::egg::result_of_indirect<T_my_idr const *>::type T_my_idrr;
PSTADE_POD_CONSTANT((T_my_idrr), my_idrr)
    = PSTADE_EGG_INDIRECT_L &my_idr PSTADE_EGG_INDIRECT_R;

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

typedef pstade::egg::result_of_pipable<T_my_plus>::type T_pipa;
PSTADE_POD_CONSTANT((T_pipa), pipa) = PSTADE_EGG_PIPABLE_L {999} PSTADE_EGG_PIPABLE_R;
T_pipa const &get_pipa1();
T_pipa const &get_pipa2();

typedef pstade::egg::result_of_ambi1<T_my_plus>::type T_auxi;
PSTADE_POD_CONSTANT((T_auxi), auxi) = PSTADE_EGG_AMBI_L {999} PSTADE_EGG_AMBI_R;
T_auxi const &get_auxi1();
T_auxi const &get_auxi2();


typedef pstade::egg::static_<pstade::egg::X_construct<int, pstade::egg::mpl_1> >::type T_construct_int;
T_construct_int const construct_int = PSTADE_EGG_STATIC();
T_construct_int const &get_cons_int1();
T_construct_int const &get_cons_int2();


#endif
