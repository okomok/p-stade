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
#define BOOST_EGG_stg     BOOST_PP_TUPLE_ELEM(2, 0, BOOST_EGG_PERFECT_STRATEGY_PARAMS)
#define BOOST_EGG_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(2, 1, BOOST_EGG_PERFECT_STRATEGY_PARAMS))


namespace boost { namespace egg {


    template<class Little>
    struct function<Little, BOOST_EGG_stg>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const &little() const 
        {
            return m_little;
        }

    // 0ary-
    #define BOOST_EGG_call_operator(R, BitSeq) \
        BOOST_EGG_call_operator_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_param,    ~, BitSeq) \
        ) \
    /**/
    #define BOOST_EGG_call_operator_aux(ArgTypes, Params) \
        template<BOOST_PP_ENUM_PARAMS(n, class A)> \
        typename apply_little<Little const, ArgTypes>::type \
        operator()(Params) const \
        { \
            return call_little(m_little, BOOST_PP_ENUM_PARAMS(n, a)); \
        } \
    /**/
    #define BOOST_EGG_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(BOOST_EGG_ac, Bit)(BOOST_PP_CAT(A, I))
    #define BOOST_EGG_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(BOOST_EGG_c, Bit) & BOOST_PP_CAT(a, I)
    #define BOOST_EGG_c0
    #define BOOST_EGG_c1 const
    #define BOOST_EGG_ac0(A) A
    #define BOOST_EGG_ac1(A) BOOST_EGG_DEDUCED_CONST(A)
        #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (BOOST_EGG_arities, <boost/egg/detail/perfect_strategy_include.hpp>)
        #include BOOST_EGG_PP_ARRAY_ITERATE()
    #undef  BOOST_EGG_ac1
    #undef  BOOST_EGG_ac0
    #undef  BOOST_EGG_c1
    #undef  BOOST_EGG_c0
    #undef  BOOST_EGG_param
    #undef  BOOST_EGG_arg_type
    #undef  BOOST_EGG_call_operator_aux
    #undef  BOOST_EGG_call_operator
    };


} } // namespace boost::egg


#undef  BOOST_EGG_arities
#undef  BOOST_EGG_stg
#undef  BOOST_EGG_PERFECT_STRATEGY_PARAMS


#else
#define n BOOST_EGG_PP_ARRAY_ITERATION()


#if n == 0

    typename apply_little<Little const>::type
    operator()() const
    {
        return call_little(m_little);
    }

#else

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_EGG_call_operator, BOOST_EGG_PP_SEQ_REPEAT((0)(1), n))

#endif


#undef  n
#endif
