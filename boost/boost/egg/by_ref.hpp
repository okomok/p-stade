#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_BY_REF_HPP
#define BOOST_EGG_BY_REF_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "./config.hpp" // BOOST_EGG_MAX_LINEAR_ARITY
#include "./detail/apply_little_n.hpp"
#include "./detail/call_little_impl.hpp"
#include "./detail/function_preamble.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    template<class Little>
    struct function<Little, by_ref>
    {
        #include BOOST_EGG_FUNCTION_PREAMBLE()

        Little m_little;
        Little little() const { return m_little; }

    // 0ary
        nullary_result_type operator()() const
        {
            return call_little_impl<
                Little, nullary_result_type
            >::call0(m_little);
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/by_ref.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(apply_little, n)<Little const, BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return call_little_impl<
            Little, typename BOOST_PP_CAT(apply_little, n)<Little const, BOOST_PP_ENUM_PARAMS(n, A)>::type
        >::BOOST_PP_CAT(call, n)(m_little, BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
