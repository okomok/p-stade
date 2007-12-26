#ifndef PSTADE_EGG_BY_PERFECT_TEMPLATE_HPP
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_HPP
#include "../detail//prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include "../detail/call_baby.hpp"
#include "../detail/meta_arg.hpp"
#include "../function_fwd.hpp"


#define PSTADE_EGG_BY_PERFECT_TEMPLATE_CALL_OPERATOR(R, BitSeq) \
    PSTADE_EGG_BY_PERFECT_TEMPLATE_CALL_OPERATOR_AUX( \
        BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_BY_PERFECT_TEMPLATE_ARG_TYPE, ~, BitSeq), \
        BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_BY_PERFECT_TEMPLATE_PARAM,    ~, BitSeq) \
    ) \
/**/

#define PSTADE_EGG_BY_PERFECT_TEMPLATE_CALL_OPERATOR_AUX(ArgTypes, Params) \
    template<BOOST_PP_ENUM_PARAMS(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, class A)> \
    typename BOOST_PP_CAT(pstade_egg_result, PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY)<ArgTypes>::type \
    operator()(Params) const \
    { \
        return pstade::egg::detail::call_baby< \
            Baby, typename BOOST_PP_CAT(pstade_egg_result, PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY)<ArgTypes>::type \
        >::call(m_baby, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY, a)); \
    } \
/**/

#define PSTADE_EGG_BY_PERFECT_TEMPLATE_ARG_TYPE(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(PSTADE_EGG_BY_PERFECT_TEMPLATE_AC, Bit)(BOOST_PP_CAT(A, I)) &
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_PARAM(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_EGG_BY_PERFECT_TEMPLATE_C, Bit) & BOOST_PP_CAT(a, I)
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_C0
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_C1 const
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_AC0(A) A
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_AC1(A) PSTADE_DEDUCED_CONST(A)


#define PSTADE_EGG_BY_PERFECT_TEMPLATE() <pstade/egg/by_perfect/detail/template_include.hpp>


#endif
