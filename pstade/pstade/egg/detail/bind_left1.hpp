#ifndef PSTADE_EGG_DETAIL_BIND_LEFT1_HPP
#define PSTADE_EGG_DETAIL_BIND_LEFT1_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind_left1(f, a1)(a2, a3)
//   is equivalent to f(a1, a2, a3).
// Notice curry2 expects it to work as "normal" bind,
// meaning that by_perfect and bound/unbound_arg is needed.


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../by_cref.hpp"
#include "../by_perfect.hpp"
#include "../fuse.hpp"
#include "../generator.hpp"
#include "../tuple/push_front.hpp"
#include "../use_variadic1.hpp"
#include "../variadic.hpp"
#include "./bound_arg.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Func, class Bound>
    struct little_bind_left1_result
    {
        Func m_func;
        Bound m_bound;

        typename unbound_arg<Bound>::type base() const
        {
            return m_bound;
        }

        template<class Myself, class Args>
        struct apply :
            result_of<
                typename result_of<
                    T_fuse(Func const&)
                >::type(typename result_of<T_tuple_push_front(Args&, typename unbound_arg<Bound>::type)>::type)
            >
        { };

        template<class Result, class Args>
        Result call(Args& args) const
        {
            return fuse(m_func)(tuple_push_front(args, m_bound));
        }
    };


    template<class Func, class Bound>
    struct result_of_bind_left1 :
        variadic<little_bind_left1_result<Func, Bound>, by_perfect>
    { };

    #define PSTADE_EGG_BIND_LEFT1_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_BIND_LEFT1_M ,
    #define PSTADE_EGG_BIND_LEFT1_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_BIND_LEFT1(F, A) PSTADE_EGG_BIND_LEFT1_L F PSTADE_EGG_BIND_LEFT1_M A PSTADE_EGG_BIND_LEFT1_R


    typedef
        generator<
            result_of_bind_left1< deduce<mpl_1, as_value>, deduce<mpl_2, as_bound_arg> >::type,
            by_cref,
            use_variadic1
        >::type
    T_bind_left1;

    PSTADE_POD_CONSTANT((T_bind_left1), bind_left1) = PSTADE_EGG_GENERATOR();


} } } // namespace pstade::egg::detail


#endif
