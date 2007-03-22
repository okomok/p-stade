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
// See http://d.hatena.ne.jp/mb2sync/20061223#p1 for more detail.
//
// This class is big, but seems not to make
// the compile-time so slower as expected.


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/use_default.hpp>


#if !defined(PSTADE_CALLABLE_MAX_ARITY)
    #define PSTADE_CALLABLE_MAX_ARITY 5
#endif


namespace pstade {


    // Add const-qualifier if rvalue is specified.
    template< class A >
    struct callable_argument :
        boost::remove_reference<
            // VC++ warns against 'A const' if 'A' is reference, so...
            typename boost::add_const<A>::type
        >
    { };


    template< class Function > // for cute error message.
    struct callable_error_non_nullary;


    PSTADE_ADL_BARRIER(callable) {


    template< class Derived, class NullaryResult = boost::use_default >
    struct callable :
        provide_sig
    {

        typedef typename
            use_default_to< NullaryResult, callable_error_non_nullary<Derived> >::type
        nullary_result_type;


        template< class Signature >
        struct result
        { }; // complete for SFINAE.


        // 0ary

        nullary_result_type // Never call 'boost::result_of', which requires 'Derived' to be complete.
        operator()() const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                nullary_result_type
            >();
        }


        // 1ary

    private:
        template< class A0 >
        struct result1 : // Prefer inheritance for SFINAE.
            Derived::BOOST_NESTED_TEMPLATE apply< Derived,
                typename callable_argument<A0>::type
            >
        { };

    public:
        template< class Self, class A0 >
        struct result<Self(A0)> :
            result1<A0>
        { };

        // Workaround:
        // Never call 'result<callable(A0&,..)>' directly;
        // a signature form makes VC7.1 fall into ETI.
        template< class A0 >
        typename result1<A0&>::type
        operator()(A0& a0) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename result1<A0&>::type
            >(a0);
        }

        template< class A0 >
        typename result1<PSTADE_DEDUCED_CONST(A0)&>::type
        operator()(A0 const& a0) const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                typename result1<PSTADE_DEDUCED_CONST(A0)&>::type
            >(a0);
        }


        // 2ary-

    #define PSTADE_call_operator(R, BitSeq) \
        PSTADE_call_operator_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param, ~, BitSeq) \
        ) \
    /**/
    #define PSTADE_call_operator_aux(ArgTypes, Params) \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        typename BOOST_PP_CAT(result, n)< ArgTypes >::type \
        operator()( Params ) const \
        { \
            return derived().BOOST_NESTED_TEMPLATE call< \
                typename BOOST_PP_CAT(result, n)< ArgTypes >::type \
            >(BOOST_PP_ENUM_PARAMS(n, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, Index, Bit) BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, Index)) &
    #define PSTADE_param(R, _, Index, Bit)    BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(A, Index) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, Index)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(X) X
    #define PSTADE_ac1(X) PSTADE_DEDUCED_CONST(X)
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
    #undef  PSTADE_call_operator_aux
    #undef  PSTADE_call_operator


    private:
        Derived const& derived() const
        {
            return static_cast<Derived const&>(*this);
        }

    }; // struct callable


    } // ADL barrier


// A nullary polymorphic function shall specialize
// 'boost::result_of' directly. These macros help.


#define PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE(NameSeq) \
    PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE_aux(PSTADE_PP_FULLNAME(NameSeq)) \
/**/

#define PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE_aux(Fullname) \
    namespace boost { \
        \
        template< > \
        struct result_of< Fullname(void) > \
        { \
            typedef Fullname::nullary_result_type type; \
        }; \
        \
        template< > \
        struct result_of< Fullname const(void) > : \
               result_of< Fullname(void) > \
        { }; \
        \
    } \
/**/


#define PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(NameSeq, ParamSeqOrCount) \
    PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE_aux(PSTADE_PP_FULLNAME(NameSeq), PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount)) \
/**/

#define PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE_aux(Fullname, ParamSeq) \
    namespace boost { \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) > \
        struct result_of< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) >(void) > \
        { \
            typedef typename Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) >::nullary_result_type type; \
        }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) > \
        struct result_of< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > const(void) > : \
               result_of< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) >(void) > \
        { }; \
        \
     } \
/**/


#define PSTADE_CALLABLE_APPLY_PARAMS(A) \
    class BOOST_PP_CAT(A, 0) BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(PSTADE_CALLABLE_MAX_ARITY), PSTADE_CALLABLE_APPLY_PARAMS_op, A) 
/**/

    #define PSTADE_CALLABLE_APPLY_PARAMS_op(Z, N, A) , class BOOST_PP_CAT(A, N) = void


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n) :
        Derived::BOOST_NESTED_TEMPLATE apply< Derived,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename callable_argument<A, >::type)
        >
    { };

public:
    template< class Self, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Self(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };


    BOOST_PP_SEQ_FOR_EACH_PRODUCT(
        PSTADE_call_operator,
        BOOST_PP_REPEAT(n, PSTADE_bits, ~)
    )


#undef n
#endif
