#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_MSVC71_RESULT_OF_HPP
#define PSTADE_EGG_DETAIL_MSVC71_RESULT_OF_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a msvc-7.1 bug;
// msvc-7.1 complains about the "const A" syntax of:
//     template<class A> ...A const... foo(A& a) { }
// if A is deduced as array type, which "../deduced_const.hpp" using 'add_const' easily works around.
// But, only in namespace scope, msvc-7.1 (fairly infrequently) fails to const-qualify 'A'
// in 'boost::result_of' parameter types if a metafunction is used:
//     template<class A> // 'add_const' below is ignored.
//     typename boost::result_of<F(typename add_const<A>::type&)>::type foo(A& a, F) { }
// So, we must delay to write 'const' for array types, then instantiate 'result_of' using 'const'.
// Fortunately, this bug doesn't occur in class scope.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>


#if !defined(PSTADE_EGG_MSVC71_RESULT_OF_MAX_ARITY)
    #define PSTADE_EGG_MSVC71_RESULT_OF_MAX_ARITY 5
#endif


namespace pstade { namespace egg { namespace detail_msvc71 {


    template<class A>
    struct const_ref;


// 1ary
    template<class Fun, class A0, class Dummy = void>
    struct result_of1;

    template<class Fun, class A0>
    struct result_of1< Fun, A0 > :
        pstade::result_of<Fun(A0)>
    { };

    // Delay to const-qualify for array type.
    template<class Fun, class A0>
    struct result_of1< Fun, const_ref<A0> > :
        pstade::result_of<Fun(A0 const&)> // Write 'const' without metafuntion for 'result_of'.
    { };


// 2ary-
    #define PSTADE_result_of(R, BitSeq) \
        PSTADE_result_of_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param,    ~, BitSeq) \
        ) \
    /**/
    #define PSTADE_result_of_aux(ArgTypes, Params) \
        template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)> \
        struct BOOST_PP_CAT(result_of, n)< Fun, ArgTypes > : \
            pstade::result_of<Fun(Params)> \
        { }; \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I))
    #define PSTADE_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit)
    #define PSTADE_c0
    #define PSTADE_c1 const&
    #define PSTADE_ac0(A) A
    #define PSTADE_ac1(A) const_ref<A>
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MSVC71_RESULT_OF_MAX_ARITY, <pstade/egg/detail/msvc71_result_of.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_result_of_aux
    #undef  PSTADE_result_of


} } } // namespace pstade::egg::detail_msvc71


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A), class Dummy = void>
    struct BOOST_PP_CAT(result_of, n);

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(PSTADE_result_of, PSTADE_PP_SEQ_REPEAT((0)(1), n))


#undef n
#endif
