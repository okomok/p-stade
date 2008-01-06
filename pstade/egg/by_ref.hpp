#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BY_REF_HPP
#define PSTADE_EGG_BY_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include "./call_little.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/nullary_result.hpp"
#include "./function_fwd.hpp"
#include "./sig_template.hpp"
#include "./unref_by.hpp"


namespace pstade { namespace egg {


    template<class Little>
    struct function<Little, by_ref>
    {
        typedef function function_type;
        typedef Little little_type;

        Little m_little;

        Little little() const
        {
            return m_little;
        }

    // 0ary
        typedef typename
            detail::nullary_result<Little, function>::type
        nullary_result_type;

        nullary_result_type operator()() const
        {
            return egg::call_little<
                Little, nullary_result_type
            >::call(m_little);
        }

    // 1ary-
        template<class FunCall>
        struct result;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/by_ref.hpp>))
        #include BOOST_PP_ITERATE()

        #include PSTADE_EGG_SIG_TEMPLATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    // This indirection is needed for msvc ETI bug.
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        Little::template apply<
            Little const,
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename unref_by_ref<A, >::type)
        >
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return egg::call_little<
            Little, typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
        >::call(m_little, BOOST_PP_ENUM_PARAMS(n, a));
    }
    

#undef n
#endif
