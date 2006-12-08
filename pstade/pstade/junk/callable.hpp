#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_CALLABLE_HPP
#define PSTADE_CALLABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// http://article.gmane.org/gmane.comp.parsers.spirit.devel/2826
//
// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This CRTP class can work around the VC7.1/8 fatal bug!!
// http://article.gmane.org/gmane.comp.lib.boost.devel/150218


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp> // inclusion guaranteed
#include <pstade/const.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/preprocessor.hpp>


#if !defined(PSTADE_CALLABLE_MAX_ARITY)
    #define PSTADE_CALLABLE_MAX_ARITY 5
#endif


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1
    #define PSTADE_CALLABLE_NEEDS_ETI_WORKAROUND
#endif


namespace pstade {


    namespace callable_detail {


        // makes rvalue const-qualified.
        template< class A >
        struct meta_argument :
            boost::remove_reference<
                typename boost::add_const<A>::type
            >
        { };


        typedef void her_t;
        typedef int  his_t;


    } // namespace callable_detail

    
    template< class Derived, class NullaryResult = void >
    struct callable :
        lambda_sig
    {
        typedef NullaryResult nullary_result_type;


        template< class Signature >
        struct result;

        // 0ary

        NullaryResult // don't call 'boost::result_of', which requires 'Derived' to be complete.
        operator()() const
        {
            return const_derived().template call<
                NullaryResult
            >();
        }


        // 1ary

        template< class A0 >
        struct result1 :
            Derived::template apply< Derived,
                typename callable_detail::meta_argument<A0>::type
            >
        { };

#if !defined(PSTADE_CALLABLE_NEEDS_ETI_WORKAROUND)

        typedef callable const self_fun_t;

        template< class Self, class A0 >
        struct result<Self(A0)> :
            result1<A0>
        { };

#else

        typedef Derived self_fun_t;

        template< class Self, class A0 >
        struct result<Self const(A0)>
        {
            typedef typename result1<A0>::type type;
        };
/*
        template< class A0 >
        struct result<Derived const(A0)>
        {
            typedef typename result1<A0>::type type;
        };

        template< class A0 >
        struct result<Derived volatile(A0)> :
            result1<A0>
        { };

        template< class A0 >
        struct result<Derived const volatile(A0)> :
            result1<A0>
        { };
*/
#endif // !defined(PSTADE_CALLABLE_NEEDS_ETI_WORKAROUND)

        template< class A0 >
        typename result<self_fun_t(A0&)>::type
        operator()(A0& a0) const
        {
            return const_derived().template call<
                typename result<self_fun_t(A0&)>::type
            >(a0);
        }

        template< class A0 >
        typename result<Derived(PSTADE_CONST(A0)&)>::type
        operator()(A0 const& a0) const
        {
            return const_derived().template call<
                typename result<self_fun_t(PSTADE_CONST(A0)&)>::type
            >(a0);
        }


        // 2ary-

    #define PSTADE_call_operator(R, BitSeq) \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        typename result<self_fun_t(BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq))>::type \
        operator()(BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param, ~, BitSeq)) const \
        { \
            return const_derived().template call< \
                typename result<self_fun_t(BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq))>::type \
            >(BOOST_PP_ENUM_PARAMS(n, a)); \
        } \
    /**/
    #define PSTADE_meta_argument(Z, N, _)     typename callable_detail::meta_argument<BOOST_PP_CAT(A, N)>::type
    #define PSTADE_arg_type(R, _, Index, Bit) BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, Index)) &
    #define PSTADE_param(R, _, Index, Bit)    BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(A, Index) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, Index)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(X) X
    #define PSTADE_ac1(X) PSTADE_CONST(X)
    #define PSTADE_bits(Z, N, _) ((0)(1))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_CALLABLE_MAX_ARITY, <pstade/callable.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_bits
    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_meta_argument
    #undef  PSTADE_call_operator

    private:
        Derived const& const_derived() const
        {
            return static_cast<Derived const&>(*this);
        }

    }; // struct callable


// 'callable' can't define 'result_type' for you.
// If a functor has nested 'result_type',
//'boost::result_of' ignores any nested 'result' specializations.


#define PSTADE_CALLABLE_NULLARY_RESULT_TYPE(NameSeq) \
    PSTADE_PP_DECLARE_TYPE(struct, NameSeq) \
    PSTADE_CALLABLE_NULLARY_RESULT_TYPE_result_of(NameSeq) \
/**/

#define PSTADE_CALLABLE_NULLARY_RESULT_TYPE_result_of(NameSeq) \
    namespace boost { \
        \
        template< > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq)(void) > \
        { \
            typedef PSTADE_PP_FULLNAME(NameSeq)::nullary_result_type type; \
        }; \
        \
        template< > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq) const(void) > \
            : result_of< PSTADE_PP_FULLNAME(NameSeq)(void) > \
        { }; \
        \
        template< > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq) volatile(void) > \
            : result_of< PSTADE_PP_FULLNAME(NameSeq)(void) > \
        { }; \
        \
        template< > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq) const volatile(void) > \
            : result_of< PSTADE_PP_FULLNAME(NameSeq)(void) > \
        { }; \
        \
    } \
/**/


#define PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE(NameSeq, ParamSeqOrCount) \
    PSTADE_PP_DECLARE_TEMPLATE(struct, NameSeq, ParamSeqOrCount) \
    PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE_result_of(NameSeq, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount)) \
/**/

#define PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE_result_of(NameSeq, ParamSeq) \
    namespace boost { \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) >(void) > \
        { \
            typedef typename PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) >::nullary_result_type type; \
        }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) > const(void) > \
            : result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) >(void) > \
        { }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) > volatile(void) > \
            : result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) >(void) > \
        { }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) > const volatile(void) > \
            : result_of< PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) >(void) > \
        { }; \
        \
    } \
/**/


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n) :
        Derived::template apply< Derived,
            BOOST_PP_ENUM(n, PSTADE_meta_argument, ~)
        >
    { };


#if !defined(PSTADE_CALLABLE_NEEDS_ETI_WORKAROUND)

    template< class Self, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Self(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM(n, PSTADE_meta_argument, ~)
        >
    { };

#else

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Derived(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM(n, PSTADE_meta_argument, ~)
        >
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Derived const(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM(n, PSTADE_meta_argument, ~)
        >
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Derived volatile(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM(n, PSTADE_meta_argument, ~)
        >
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Derived const volatile(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM(n, PSTADE_meta_argument, ~)
        >
    { };

#endif //  !defined(PSTADE_CALLABLE_NEEDS_ETI_WORKAROUND)


BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    PSTADE_call_operator,
    BOOST_PP_REPEAT(n, PSTADE_bits, ~)
)


#undef n
#endif
