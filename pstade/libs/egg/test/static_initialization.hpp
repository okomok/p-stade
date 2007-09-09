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


struct baby_my_id
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


// Note that if the ODR violation baster:
//   http://lists.boost.org/Archives/boost/2007/06/123353.php
// is applied to my_id, kiils the initialization of my_idr.
// An address constant expression seems to break down static-initialization.
typedef pstade::egg::function<baby_my_id> op_my_id;
PSTADE_POD_CONSTANT((op_my_id), my_id)
    = {{12}};

op_my_id const &get_my_id1();
op_my_id const &get_my_id2();


typedef pstade::egg::result_of_indirect<op_my_id const *>::type op_my_idr;
PSTADE_POD_CONSTANT((op_my_idr), my_idr)
    = PSTADE_EGG_INDIRECT_L &my_id PSTADE_EGG_INDIRECT_R;

op_my_idr const &get_my_idr1();
op_my_idr const &get_my_idr2();


#endif
