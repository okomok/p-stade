#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_PERFECT_FORWARDING_PARAMS)
    #error Please define PSTADE_EGG_PERFECT_FORWARDING_PARAMS
#endif

#define PSTADE_baby    BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_PERFECT_FORWARDING_PARAMS)
#define PSTADE_arities BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_PERFECT_FORWARDING_PARAMS)


    // header
        typedef function function_type;
        typedef PSTADE_baby baby_type;

        PSTADE_baby m_baby;

        PSTADE_baby baby() const
        {
            return m_baby;
        }

        typedef typename
            detail::nullary_result<PSTADE_baby, function>::type
        nullary_result_type;

    // 0ary-
        template<class FunCall>
        struct result;

    #define PSTADE_call_operator(R, BitSeq) \
        PSTADE_call_operator_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param,    ~, BitSeq) \
        ) \
    /**/
    #define PSTADE_call_operator_aux(ArgTypes, Params) \
        template<BOOST_PP_ENUM_PARAMS(n, class A)> \
        typename BOOST_PP_CAT(result, n)<ArgTypes>::type \
        operator()(Params) const \
        { \
            return detail::call_baby< \
                PSTADE_baby, typename BOOST_PP_CAT(result, n)<ArgTypes>::type \
            >::call(m_baby, BOOST_PP_ENUM_PARAMS(n, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I)) &
    #define PSTADE_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, I)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(A) A
    #define PSTADE_ac1(A) PSTADE_DEDUCED_CONST(A)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(PSTADE_arities)), <pstade/egg/detail/perfect_forwarding_include.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_call_operator_aux
    #undef  PSTADE_call_operator

        #include PSTADE_EGG_SIG_TEMPLATE()


#undef  PSTADE_arities
#undef  PSTADE_baby
#undef  PSTADE_EGG_PERFECT_FORWARDING_PARAMS


#else
#define n BOOST_PP_SEQ_ELEM(BOOST_PP_ITERATION(), PSTADE_arities)


#if n == 0

    nullary_result_type operator()() const
    {
        return detail::call_baby<
            PSTADE_baby, nullary_result_type
        >::call(m_baby);
    }

#else

    // This indirection is needed for msvc ETI bug.
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        PSTADE_baby::template apply<
            PSTADE_baby,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename detail::meta_arg<A, >::type)
        >
    { };

    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(PSTADE_call_operator, PSTADE_PP_SEQ_REPEAT((0)(1), n))

#endif // n == 0


#undef n
#endif
