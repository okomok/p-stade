#ifndef PSTADE_EGG_COMPOSE_HPP
#define PSTADE_EGG_COMPOSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/baby_fused_compose_result.hpp"
#include "./function.hpp"
#include "./function_by_value.hpp"
#include "./object.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    // The nullary result type must be explicitly specified.
    // 'result_of<F(result_of<G()>::type)>::type' is always instantiated,
    // but it may be ill-formed, if 'result_of<G()>::type' is 'void', or
    // an invalid type like 'tuples::null_type' which Boost.Lambda returns instead of 'void'.
    // If such an invalid type is always 'void', then 'result_of<F()>::type' is always well-formed.
    // But, it is not a general solution. "compose2" to call 'f(g1, g2)' would be ill-formed after all.


    template<class F, class G, class NullaryResult = boost::use_default>
    struct compose_result :
        unfuse_result<
            function< detail::baby_fused_compose_result<F, G> >,
            boost::use_default,
            NullaryResult
        >
    { };


    #define PSTADE_EGG_COMPOSE_RESULT_INITIALIZER(F, G) \
        { { { { F, G } }, {} } } \
    /**/


    template<class NullaryResult>
    struct baby_compose
    {
        template<class Myself, class F, class G>
        struct apply :
            compose_result<F, G, NullaryResult>
        { };

        template<class Result, class F, class G>
        Result call(F f, G g) const
        {
            Result result = PSTADE_EGG_COMPOSE_RESULT_INITIALIZER(f, g);
            return result;
        }
    };


    template<class NullaryResult = boost::use_default>
    struct xp_compose
    {
        typedef
            function_by_value< baby_compose<NullaryResult> >
        type;
    };


    typedef xp_compose<>::type op_compose;
    PSTADE_EGG_OBJECT((op_compose), compose) = { {} };


} } // namespace pstade::egg


#endif
