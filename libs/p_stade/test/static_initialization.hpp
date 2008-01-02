#ifndef PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP
#define PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Base on Eric Niebler's example.


#include <pstade/egg/indirect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>


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

    int touch;
};


typedef pstade::egg::function<little_my_id> T_my_id;
PSTADE_POD_CONSTANT((T_my_id), my_id)
    = {{12}};

T_my_id const &get_my_id1();
T_my_id const &get_my_id2();


typedef pstade::egg::result_of_indirect<T_my_id const *>::type T_my_idr;
PSTADE_POD_CONSTANT((T_my_idr), my_idr)
    = PSTADE_EGG_INDIRECT_L &my_id PSTADE_EGG_INDIRECT_R;

T_my_idr const &get_my_idr1();
T_my_idr const &get_my_idr2();


#endif
