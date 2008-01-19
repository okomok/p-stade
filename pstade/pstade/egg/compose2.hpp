#ifndef PSTADE_EGG_COMPOSE2_HPP
#define PSTADE_EGG_COMPOSE2_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_value.hpp"
#include "./fuse.hpp"
#include "./generator.hpp"
#include "./use_variadic1.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace compose2_detail {


        template<class F, class G1, class G2>
        struct little_result
        {
            F m_f;
            G1 m_g1;
            G2 m_g2;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    F const(
                        typename result_of<typename result_of<T_fuse(G1 const&)>::type(ArgTuple&)>::type,
                        typename result_of<typename result_of<T_fuse(G2 const&)>::type(ArgTuple&)>::type
                    )
                >
            { };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                return m_f(fuse(m_g1)(args), fuse(m_g2)(args));
            }
        };


    } // namespace compose2_detail


    template<class F, class G1, class G2, class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct result_of_compose2 :
        variadic<compose2_detail::little_result<F, G1, G2>, Strategy, NullaryResult>
    { };

    #define PSTADE_EGG_COMPOSE2_L  PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_COMPOSE2_M1 ,
    #define PSTADE_EGG_COMPOSE2_M2 ,
    #define PSTADE_EGG_COMPOSE2_R  } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_COMPOSE2(F, G1, G2) PSTADE_EGG_COMPOSE2_L F PSTADE_EGG_COMPOSE2_M1 G1 PSTADE_EGG_COMPOSE2_M2 G2 PSTADE_EGG_COMPOSE2_R


    template<class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct X_compose2 :
        generator<
            typename result_of_compose2<deduce<mpl_1, as_value>, deduce<mpl_2, as_value>, deduce<mpl_3, as_value>, NullaryResult, Strategy>::type,
            by_value,
            use_variadic1
        >::type
    { };

    typedef X_compose2<>::function_type T_compose2;
    PSTADE_POD_CONSTANT((T_compose2), compose2) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
