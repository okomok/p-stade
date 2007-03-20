#ifndef PSTADE_CAST_FUNCTION_HPP
#define PSTADE_CAST_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


#include <boost/utility/result_of.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>


#define PSTADE_CAST_FUNCTION1(Name, Op, ParamSeqOrCount) \
    PSTADE_CAST_FUNCTION1_aux(Name, Op, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount)) \
/**/

    #define PSTADE_CAST_FUNCTION1_aux(Name, Op, Seq) \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0> inline \
        typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(A0&)>::type \
        Name(A0& a0 PSTADE_CONST_OVERLOADED(A0)) \
        { \
            return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0); \
        } \
        \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0> inline \
        typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(PSTADE_DEDUCED_CONST(A0)&)>::type \
        Name(A0 const& a0) \
        { \
            return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0); \
        } \
    /**/


#define PSTADE_CAST_FUNCTION2(Name, Op, ParamSeqOrCount) \
    PSTADE_CAST_FUNCTION2_aux(Name, Op, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount)) \
/**/

    #define PSTADE_CAST_FUNCTION2_aux(Name, Op, Seq) \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0, class A1> inline \
        typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(A0&, A1&)>::type \
        Name(A0& a0, A1& a1 PSTADE_CONST_OVERLOADED_SEQ((A0)(A1))) \
        { \
            return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0, a1); \
        } \
        \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0, class A1> inline \
        typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(A0&, PSTADE_DEDUCED_CONST(A1)&)>::type \
        Name(A0& a0, A1 const& a1 PSTADE_CONST_OVERLOADED_SEQ((A0)(A1))) \
        { \
            return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0, a1); \
        } \
        \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0, class A1> inline \
        typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(PSTADE_DEDUCED_CONST(A0)&, A1&)>::type \
        Name(A0 const& a0, A1& a1 PSTADE_CONST_OVERLOADED_SEQ((A0)(A1))) \
        { \
            return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0, a1); \
        } \
        \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0, class A1> inline \
        typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(PSTADE_DEDUCED_CONST(A0)&, PSTADE_DEDUCED_CONST(A1)&)>::type \
        Name(A0 const& a0, A1 const& a1 PSTADE_CONST_OVERLOADED_SEQ((A0)(A1))) \
        { \
            return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0, a1); \
        } \
    /**/


#endif
