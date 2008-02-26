#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_VC7_1_RESULT_OF_HPP
#define BOOST_EGG_DETAIL_VC7_1_RESULT_OF_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Used in "../explict.hpp" for msvc-7.1 bug workaround;
// msvc-7.1 complains about the "const A" syntax of:
//     template<class A> ...A const... foo(A &a) { }
// if A is deduced as array type, which "./deduced_const.hpp" using 'add_const' easily works around.
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
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/preprocessor/bits_enum.hpp>
#include <boost/egg/preprocessor/for_each_bits.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/boost_workaround.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
    #error This big header is used only with msvc-7.1.
#endif


namespace boost { namespace egg { namespace vc7_1_detail {


    template<class A>
    struct const_ref;


    // supports only lvalue.
    #define BOOST_EGG_spec(R, Bits, _) \
        template<class Fun, BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), class A)> \
        struct BOOST_PP_CAT(result_of, n)<Fun, BOOST_EGG_PP_BITS_ENUM_R(R, Bits, BOOST_EGG_match_w0, BOOST_EGG_match_w1, ~)> : \
            result_of_<Fun(BOOST_EGG_PP_BITS_ENUM_R(R, Bits, BOOST_EGG_fwd_w0, BOOST_EGG_fwd_w1, ~))> \
        { }; \
    /**/

    #define BOOST_EGG_match_w0(R, I, _) BOOST_PP_CAT(A, I) &
    #define BOOST_EGG_match_w1(R, I, _) const_ref<BOOST_PP_CAT(A, I)>
    #define BOOST_EGG_fwd_w0(R, I, _) BOOST_PP_CAT(A, I) &
    #define BOOST_EGG_fwd_w1(R, I, _) BOOST_PP_CAT(A, I) const &

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_ARITY, <boost/egg/detail/vc7_1_result_of.hpp>))
        #include BOOST_PP_ITERATE()

    #undef  BOOST_EGG_fwd_w1
    #undef  BOOST_EGG_fwd_w0
    #undef  BOOST_EGG_match_w1
    #undef  BOOST_EGG_match_w0
    #undef  BOOST_EGG_spec


} } } // namespace boost::egg::vc7_1_detail


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A), class Dummy = void>
    struct BOOST_PP_CAT(result_of, n);

    BOOST_EGG_PP_FOR_EACH_BITS(n, BOOST_EGG_spec, ~)


#undef  n
#endif
