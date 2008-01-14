#ifndef BOOST_EGG_COMPOSE_HPP
#define BOOST_EGG_COMPOSE_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/result_of.hpp>
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
    // But, it is not a general solution. "compose2" to call 'f(g1, g2)' would be ill-formed after all.


    namespace compose_detail {


        template<class F, class G>
        struct little_fused_result
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


    } // namespace compose_detail


    template<class F, class G, class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct result_of_compose :
        result_of_unfuse<
            function<compose_detail::little_fused_result<F, G>, by_cref>,
            boost::use_default,
            NullaryResult,
            Strategy
        >
    { };


    // BOOST_EGG_UNFUSE_L { { F, G } } BOOST_EGG_UNFUSE_M BOOST_EGG_UNFUSE_DEFAULT_PACK BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_COMPOSE_L BOOST_EGG_UNFUSE_L { {
    #define BOOST_EGG_COMPOSE_M ,
    #define BOOST_EGG_COMPOSE_R } } BOOST_EGG_UNFUSE_M BOOST_EGG_UNFUSE_DEFAULT_PACK BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_COMPOSE(F, G) BOOST_EGG_COMPOSE_L F BOOST_EGG_COMPOSE_M G BOOST_EGG_COMPOSE_R


    namespace compose_detail {


        template<class NullaryResult, class Strategy>
        struct little
        {
            template<class Myself, class F, class G>
            struct apply :
                result_of_compose<F, G, NullaryResult, Strategy>
            { };

            template<class Result, class F, class G>
            Result call(F f, G g) const
            {
                Result r = BOOST_EGG_COMPOSE(f, g);
                return r;
            }
        };


    } // namespace compose_detail


    template<class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct X_compose :
        function<compose_detail::little<NullaryResult, Strategy>, by_value>
    { };

    typedef X_compose<>::function_type T_compose;
    PSTADE_POD_CONSTANT((T_compose), compose) = {{}};


} } // namespace pstade::egg


#endif
