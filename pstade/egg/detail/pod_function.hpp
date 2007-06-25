#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_POD_FUNCTION_HPP
#define PSTADE_EGG_DETAIL_POD_FUNCTION_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Turns DefaultConstructible Function into a POD.


#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include "../nullary_result_of.hpp"
#include "./error_non_nullary.hpp"
#include "./nonref_arg.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Function>
    struct pod_function
    {
        typedef typename
            boost::result_of<Function()>::type
        nullary_result_type;

        // 0ary
        nullary_result_type operator()() const
        {
            return Function()();
        }

        template<class FunCall>
        struct result;

        // 1ary-
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
            return Function()(BOOST_PP_ENUM_PARAMS(n, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I)) &
    #define PSTADE_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, I)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(A) A
    #define PSTADE_ac1(A) PSTADE_DEDUCED_CONST(A)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/pod_function.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_call_operator_aux
    #undef  PSTADE_call_operator
    };


} } } // namespace pstade::egg::detail


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::detail::pod_function, 1)


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        boost::result_of<
            Function(PSTADE_PP_ENUM_PARAMS_WITH(n, typename nonref_arg<A, >::type &))
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };


    BOOST_PP_SEQ_FOR_EACH_PRODUCT(PSTADE_call_operator, PSTADE_PP_SEQ_REPEAT((0)(1), n))


#undef n
#endif
