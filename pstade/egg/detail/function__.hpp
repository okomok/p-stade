#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNCTION_HPP
#define PSTADE_EGG_FUNCTION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/void.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>
#include "../detail/as_mpl_lambda.hpp"
#include "./constant.hpp"
#include "./detail/config.hpp"
#include "./detail/nonref_arg.hpp"


namespace pstade { namespace egg {


    template<class Lambda>
    struct function_error_non_nullary;


    template<class Lambda, class NullaryResult = boost::use_default>
    struct function
    {
        typedef typename
            if_use_default< NullaryResult, function_error_non_nullary<Lambda> >::type
        nullary_result_type;

        template<class FunCall>
        struct result;

        // These are redefined in 'resultn'.
    #define PSTADE_typedef_default_arg(Z, N, _) typedef boost::mpl::void_ BOOST_PP_CAT(arg, N);
        BOOST_PP_REPEAT(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, PSTADE_typedef_default_arg, ~)
    #undef  PSTADE_typedef_default_arg

        // 0ary
        nullary_result_type operator()() const
        {
            typedef typename boost::mpl::apply0<Lambda>::type impl_t;
            return impl_t()();
        }

        // 1ary-
    # define PSTADE_typedef_arg(Z, N, _) \
        typedef typename detail::nonref_arg<BOOST_PP_CAT(A, N)>::type BOOST_PP_CAT(arg, N); \
    /**/
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
            typedef typename BOOST_PP_CAT(result, n)<ArgTypes>::impl impl_t; \
            return impl_t()(BOOST_PP_ENUM_PARAMS(n, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I)) &
    #define PSTADE_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, I)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(A) A
    #define PSTADE_ac1(A) PSTADE_DEDUCED_CONST(A)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_FUNCTION_MAX_ARITY, <pstade/egg/function.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_call_operator_aux
    #undef  PSTADE_call_operator
    #undef  PSTADE_typedef_arg

        // Todo:
        // PSTADE_PROVIDE_SIG(...)

#if defined(PSTADE_EGG_CANT_BE_A_POD)
        function() { }
#endif
    }; // struct function


    #define PSTADE_EGG_FUNCTION(O, L) \
        namespace BOOST_PP_CAT(pstade_egg_function_workarea_of_, O) { \
            using namespace boost::mpl::placeholders; \
            typedef pstade::egg::function<PSTADE_DETAIL_AS_MPL_LAMBDA(L)> op; \
        } \
        typedef BOOST_PP_CAT(pstade_egg_function_workarea_of_, O)::op BOOST_PP_CAT(op_, O); \
        PSTADE_EGG_CONSTANT(O, (BOOST_PP_CAT(op_, O)) \
    /**/


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    // msvc needs this helper metafunction to avoid ETI.
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n)
    {
        BOOST_PP_REPEAT(n, PSTADE_typedef_arg, ~)

        typedef typename
            BOOST_PP_CAT(boost::mpl::apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
                Lambda, BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, arg)
            >::type
        impl;

        typedef typename impl::result_type type;
    };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };


    BOOST_PP_SEQ_FOR_EACH_PRODUCT(PSTADE_call_operator, PSTADE_PP_SEQ_REPEAT((0)(1), n))


#undef n
#endif
