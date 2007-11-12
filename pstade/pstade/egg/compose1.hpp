#ifndef PSTADE_EGG_COMPOSE1_HPP
#define PSTADE_EGG_COMPOSE1_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
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


    // The nullary result type must be explicitly specified.
    // 'result_of<F(result_of<G()>::type)>::type' is always instantiated,
    // but it may be ill-formed, if 'result_of<G()>::type' is 'void', or
    // an invalid type like 'tuples::null_type' which Boost.Lambda returns instead of 'void'.
    // If such an invalid type is always 'void', then 'result_of<F()>::type' is always well-formed.
    // But, it is not a general solution. "compose12" to call 'f(g1, g2)' would be ill-formed after all.


    namespace compose1_detail {


        template<class F, class G>
        struct baby_fused_result
        {
            F m_f;
            G m_g;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    F const(typename result_of<typename result_of<T_fuse(G const&)>::type(ArgTuple&)>::type)
                >
            { };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                return m_f(fuse(m_g)(args));
            }
        };


    } // namespace compose1_detail


    template<class F, class G, class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct result_of_compose1 :
        result_of_unfuse<
            function<compose1_detail::baby_fused_result<F, G>, by_cref>,
            boost::use_default,
            NullaryResult,
            Strategy
        >
    { };


    // PSTADE_EGG_UNFUSE_L { { F, G } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_COMPOSE1_L PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_COMPOSE1_M ,
    #define PSTADE_EGG_COMPOSE1_R } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R


    namespace compose1_detail {


        template<class NullaryResult>
        struct baby
        {
            template<class Myself, class F, class G>
            struct apply :
                result_of_compose1<F, G, NullaryResult>
            { };

            template<class Result, class F, class G>
            Result call(F f, G g) const
            {
                Result r = PSTADE_EGG_COMPOSE1_L f PSTADE_EGG_COMPOSE1_M g PSTADE_EGG_COMPOSE1_R;
                return r;
            }
        };


        template<class NullaryResult>
        struct pod_
        {
            typedef function<baby<NullaryResult>, by_value> type;
        };


    } // namespace compose1_detail


    template<class NullaryResult = boost::use_default>
    struct X_compose1 :
        compose1_detail::pod_<NullaryResult>::type
    {
        typedef typename compose1_detail::pod_<NullaryResult>::type pod_type;
    };


    typedef X_compose1<>::pod_type T_compose1;
    PSTADE_POD_CONSTANT((T_compose1), compose1) = {{}};


} } // namespace pstade::egg


#endif
