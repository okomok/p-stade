#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BY_VALUE_HPP
#define PSTADE_EGG_BY_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A "movable type" like 'auto_ptr' must be called by value.
// "./by_perfect.hpp" makes rvalue unmovable.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/apply_little_n.hpp"
#include "./detail/call_little_impl.hpp"
#include "./detail/unref.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    template<class Little>
    struct function<Little, by_value>
    {
        #define  PSTADE_EGG_FUNCTION_PREAMBLE_PARAMS (Little, m_little)
        #include PSTADE_EGG_FUNCTION_PREAMBLE()

    // 0ary
        nullary_result_type operator()() const
        {
            return detail::call_little_impl<
                Little, nullary_result_type
            >::call(m_little);
        }

    // 1ary-
        template<class FunCall>
        struct result;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/by_value.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(apply_little, n)<
            Little const,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename detail::unref_by_value<A, >::type)
        >
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(apply_little, n)<Little const, BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
    {
        return detail::call_little_impl<
            Little, typename BOOST_PP_CAT(apply_little, n)<Little const, BOOST_PP_ENUM_PARAMS(n, A)>::type
        >::call(m_little, BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
