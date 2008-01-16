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
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace compose2_detail {


        template<class F, class G1, class G2>
        struct little_fused_result
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


    template<class F, class G1, class G2, class Strategy = boost::use_default, class NullaryResult = boost::use_default>
    struct result_of_compose2 :
        result_of_unfuse<
            function<compose2_detail::little_fused_result<F, G1, G2>, by_cref>,
            boost::use_default,
            NullaryResult,
            Strategy
        >
    { };


    // PSTADE_EGG_UNFUSE_L { { F, G1, G2 } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_COMPOSE2_L  PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_COMPOSE2_M1 ,
    #define PSTADE_EGG_COMPOSE2_M2 ,
    #define PSTADE_EGG_COMPOSE2_R  } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_COMPOSE2(F, G1, G2) PSTADE_EGG_COMPOSE2_L F PSTADE_EGG_COMPOSE2_M1 G1 PSTADE_EGG_COMPOSE2_M2 G2 PSTADE_EGG_COMPOSE2_R


    namespace compose2_detail {


        template<class Strategy, class NullaryResult>
        struct little
        {
            template<class Myself, class F, class G1, class G2>
            struct apply :
                result_of_compose2<F, G1, G2, Strategy, NullaryResult>
            { };

            template<class Result, class F, class G1, class G2>
            Result call(F f, G1 g, G2 h) const
            {
                Result r = PSTADE_EGG_COMPOSE2(f, g, h);
                return r;
            }
        };


    } // namespace compose2_detail


    template<class Strategy = boost::use_default, class NullaryResult = boost::use_default>
    struct X_compose2 :
        function<compose2_detail::little<Strategy, NullaryResult>, by_value>
    { };


    typedef X_compose2<>::function_type T_compose2;
    PSTADE_POD_CONSTANT((T_compose2), compose2) = {{}};


} } // namespace pstade::egg


#endif
