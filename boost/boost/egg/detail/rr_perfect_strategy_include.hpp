#ifndef BOOST_PP_IS_ITERATING


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_PERFECT_STRATEGY_PARAMS)
    #error Please define BOOST_EGG_PERFECT_STRATEGY_PARAMS.
#endif
#define PSTADE_stg     BOOST_PP_TUPLE_ELEM(2, 0, BOOST_EGG_PERFECT_STRATEGY_PARAMS)
#define PSTADE_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(2, 1, BOOST_EGG_PERFECT_STRATEGY_PARAMS))


namespace boost { namespace egg {


    template<class Little>
    struct function<Little, PSTADE_stg>
    {
        #include BOOST_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const &little() const 
        {
            return m_little;
        }

    // 0ary-
        #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (PSTADE_arities, <boost/egg/detail/native_perfect_strategy_include.hpp>)
        #include BOOST_EGG_PP_ARRAY_ITERATE()
    };


} } // namespace boost::egg


#undef  PSTADE_arities
#undef  PSTADE_stg
#undef  BOOST_EGG_PERFECT_STRATEGY_PARAMS


#else
#define n BOOST_EGG_PP_ARRAY_ITERATION()


    BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS(n, class A)
    typename apply_little<
        Little const
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, typename boost::remove_reference<A, >::type BOOST_PP_INTERCEPT)
    >::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &&a)) const
    {
        // Neither egg::forward nor std::forward is used so that LittleFunction can take lvalues.
        return call_little(m_little BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
