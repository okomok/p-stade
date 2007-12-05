#ifndef PSTADE_EGG_DETAIL_DECREMENT_ARITY_HPP
#define PSTADE_EGG_DETAIL_DECREMENT_ARITY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// bind1(bind1, f)(a1, a2, a3)
//   is equivalent to
// lambda::bind(bind1, f, lamba::_1, lambda::_2, lambda::_3)(a1, a2, a3)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "../function.hpp"
#include "./bind1.hpp"


namespace pstade { namespace egg { namespace detail {


    struct baby_decrement_arity
    {
        template<class Myself, class Function>
        struct apply :
            result_of<
                op_bind1(op_bind1 const&, Function&)
            >
        { };

        template<class Result, class Function>
        Result call(Function& fun) const
        {
            return bind1(bind1, fun);
        }
    };


    typedef function<baby_decrement_arity> op_decrement_arity;
    PSTADE_POD_CONSTANT((op_decrement_arity), decrement_arity) = {{}};


} } } // namespace pstade::egg::detail


#endif
