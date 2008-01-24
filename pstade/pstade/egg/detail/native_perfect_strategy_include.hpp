#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_HAS_RVALUE_REFS)
    #error This works only with rvalue references.
#endif


#if !defined(PSTADE_EGG_PERFECT_STRATEGY_PARAMS)
    #error Please define PSTADE_EGG_PERFECT_STRATEGY_PARAMS.
#endif
#define PSTADE_stg     BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_PERFECT_STRATEGY_PARAMS)
#define PSTADE_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_PERFECT_STRATEGY_PARAMS))


namespace pstade { namespace egg {


    template<class Little>
    struct function<Little, PSTADE_stg>
    {
        #include PSTADE_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const& little() const 
        {
            return m_little;
        }

    // 0ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_arities)), <pstade/egg/detail/native_perfect_strategy_include.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#undef  PSTADE_arities
#undef  PSTADE_stg
#undef  PSTADE_EGG_PERFECT_STRATEGY_PARAMS


#else
#define n BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), PSTADE_arities)


#if n == 0

    nullary_result_type operator()() const
    {
        return call_little_impl<
            Little, nullary_result_type
        >::call0(m_little);
    }

#else

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(apply_little, n)<Little const, PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::remove_reference<A, >::type)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, && a)) const
    {
        return call_little_impl<
            Little, typename BOOST_PP_CAT(apply_little, n)<Little const, PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::remove_reference<A, >::type)>::type
        >::BOOST_PP_CAT(call, n)(m_little, BOOST_PP_ENUM_PARAMS(n, a));
    }

#endif // n == 0


#undef n
#endif
