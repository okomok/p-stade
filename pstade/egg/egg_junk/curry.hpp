#ifndef PSTADE_EGG_CURRY_HPP
#define PSTADE_EGG_CURRY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// curry2 :: ((a1,a2) -> b) -> a1 -> a2 -> b
// curry2 f x y = f (x,y)
// -- curry2 f x y = (bind f x) y
// -- curry2 f x y = (decrement_arity f) x y
//
// curry3 :: ((a1,a2,a3) -> b) -> a1 -> a2 -> a3 -> b
// curry3 f x y z = f (x,y,z) -- curry3 f x y z = bind (bind2 f x y) z


#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./detail/bind.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    struct baby_curry1
    {
        template<class Myself, class Function1>
        struct apply :
            pass_by_value<Function1>
        { };

        template<class Result, class Function1>
        Result call(Function1& fun1) const
        {
            return fun1;
        }
    };

    typedef function<baby_curry1> op_curry1;
    PSTADE_POD_CONSTANT((op_curry1), curry1) = {{}};


    struct baby_curry2
    {
        template<class Myself, class Function2>
        struct apply :
            result_of<
                detail::op_bind(detail::op_bind const&, Function2&)
            >
        { };

        template<class Result, class Function2>
        Result call(Function2& fun2) const
        {
            // bind(bind, fun2)(a1)(a2)
            // => bind(fun2, a1)(a2)
            // => fun2(a1, a2)
            return detail::bind(detail::bind, fun2);
        }
    };

    typedef function<baby_curry2> op_curry2;
    PSTADE_POD_CONSTANT((op_curry2), curry2) = {{}};


    struct baby_curry3
    {
        template<class Myself, class Function3>
        struct apply :
            result_of<
                op_curry2(
                    typename result_of<
                        detail::op_bind(detail::op_bind const&, Function3&)
                    >::type
                )
            >
        { };

        template<class Result, class Function3>
        Result call(Function3& fun3) const
        {
            // curry2(bind(bind, fun3))(a1)(a2)(a3)
            // => bind(bind, fun3)(a1, a2)(a3)
            // => bind(fun3, a1, a2)(a3)
            // => fun3(a1, a2, a3)
            return curry2(
                detail::bind(detail::bind, fun3)
            );
        }
    };

    typedef function<baby_curry3> op_curry3;
    PSTADE_POD_CONSTANT((op_curry3), curry3) = {{}};


    struct baby_curry4
    {
        template<class Myself, class Function4>
        struct apply :
            result_of<
                op_curry3(
                    typename result_of<
                        detail::op_bind(detail::op_bind const&, Function4&)
                    >::type
                )
            >
        { };

        template<class Result, class Function4>
        Result call(Function4& fun4) const
        {
            // curry3(bind(bind, fun4))(a1)(a2)(a3)(a4)
            // => bind(bind, fun4)(a1, a2, a3)(a4)
            // => bind(fun4, a1, a2, a3)(a4)
            // => fun4(a1, a2, a3, a4)
            return curry3(
                detail::bind(detail::bind, fun4)
            );
        }
    };

    typedef function<baby_curry4> op_curry4;
    PSTADE_POD_CONSTANT((op_curry4), curry4) = {{}};


    struct baby_curry5
    {
        template<class Myself, class Function5>
        struct apply :
            result_of<
                op_curry4(
                    typename result_of<
                        detail::op_bind(detail::op_bind const&, Function5&)
                    >::type
                )
            >
        { };

        template<class Result, class Function5>
        Result call(Function5& fun5) const
        {
            return curry4(
                detail::bind(detail::bind, fun5)
            );
        }
    };

    typedef function<baby_curry5> op_curry5;
    PSTADE_POD_CONSTANT((op_curry5), curry5) = {{}};


} } // namespace pstade::egg


#endif

