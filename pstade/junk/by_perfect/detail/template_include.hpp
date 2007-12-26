

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY)
    #error Please define PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY.
#endif


    // This indirection is needed for msvc ETI.
    template<BOOST_PP_ENUM_PARAMS(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, class A)>
    struct BOOST_PP_CAT(pstade_egg_result, PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY) :
        Baby::template apply<
            Baby,
            PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, typename pstade::egg::detail::meta_arg<A, >::type)
        >
    { };

    template<class Fun, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, A))> :
        BOOST_PP_CAT(pstade_egg_result, PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY)<
            BOOST_PP_ENUM_PARAMS(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, A)
        >
    { };

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(PSTADE_EGG_BY_PERFECT_TEMPLATE_CALL_OPERATOR, PSTADE_PP_SEQ_REPEAT((0)(1), PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY))


#undef  PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY
