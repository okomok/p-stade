#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_VC7_1_RESULT_OF_HPP
#define BOOST_EGG_DETAIL_VC7_1_RESULT_OF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a msvc-7.1 bug;
// msvc-7.1 complains about the "const A" syntax of:
//     template<class A> ...A const... foo(A &a) { }
// if A is deduced as array type, which <boost/egg/deduced_const.hpp> using 'add_const' easily works around.
// But, only in namespace scope, msvc-7.1 (fairly infrequently) fails to const-qualify 'A'
// in 'boost::result_of' parameter types if a metafunction is used:
//     template<class A> // 'add_const' below is ignored.
//     typename boost::result_of<F(typename add_const<A>::type &)>::type foo(A &a, F) { }
// So, we must delay to write 'const' for array types, then instantiate 'result_of' using 'const'.
// In other words, this bug introduces "Metafunction Forwarding Problem".
// Fortunately, this bug doesn't occur in class scope.
// Notice EGG_ARRAY_RESURRECT is metafunction, so that it still doesn't work.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/pp_seq_repeat.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
    #error This header is used only with msvc-7.1.
#endif


namespace boost { namespace egg { namespace detail_vc7_1 {


    template<class A>
    struct const_ref;


// 1ary
    template<class Fun, class A0, class Dummy = void>
    struct result_of1;

    template<class Fun, class A0>
    struct result_of1< Fun, A0 > :
        result_of_<Fun(A0)>
    { };

    // Delay to const-qualify for array type.
    template<class Fun, class A0>
    struct result_of1< Fun, const_ref<A0> > :
        result_of_<Fun(A0 const &)> // Write 'const' without metafuntion for 'result_of'.
    { };


// 2ary-
    #define BOOST_EGG_result_of(R, BitSeq) \
        BOOST_EGG_result_of_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_param,    ~, BitSeq) \
        ) \
    /**/
    #define BOOST_EGG_result_of_aux(ArgTypes, Params) \
        template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)> \
        struct BOOST_PP_CAT(result_of, n)< Fun, ArgTypes > : \
            boost::egg::result_of_<Fun(Params)> \
        { }; \
    /**/
    #define BOOST_EGG_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(BOOST_EGG_ac, Bit)(BOOST_PP_CAT(A, I))
    #define BOOST_EGG_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(BOOST_EGG_c, Bit)
    #define BOOST_EGG_c0
    #define BOOST_EGG_c1 const &
    #define BOOST_EGG_ac0(A) A
    #define BOOST_EGG_ac1(A) const_ref<A>
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, BOOST_EGG_MAX_ARITY, <boost/egg/detail/vc7_1_result_of.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_ac1
    #undef  BOOST_EGG_ac0
    #undef  BOOST_EGG_c1
    #undef  BOOST_EGG_c0
    #undef  BOOST_EGG_param
    #undef  BOOST_EGG_arg_type
    #undef  BOOST_EGG_result_of_aux
    #undef  BOOST_EGG_result_of


} } } // namespace boost::egg::detail_vc7_1


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A), class Dummy = void>
    struct BOOST_PP_CAT(result_of, n);

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_EGG_result_of, BOOST_EGG_PP_SEQ_REPEAT((0)(1), n))


#undef  n
#endif
