#ifndef BOOST_EGG_EXPLICIT_HPP
#define BOOST_EGG_EXPLICIT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS
#include <boost/egg/preprocessor/seq_enum_args.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>
#include <boost/egg/preprocessor/to_template_param_seq.hpp>


#if defined(BOOST_EGG_HAS_RVALUE_REFS)


    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/egg/detail/std_forward.hpp>
    #include <boost/egg/result_of.hpp>


    #define BOOST_EGG_EXPLICIT(N, Name, X_, Params) \
        BOOST_EGG_EXPLICIT_aux(N, Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params)) \
    /**/

        #define BOOST_EGG_EXPLICIT_aux(N, Name, X_, Params) \
            template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T) BOOST_PP_ENUM_TRAILING_PARAMS(N, class A)> inline \
            typename boost::egg::result_of_<X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>( \
                BOOST_PP_ENUM_PARAMS(N, A) \
            )>::type \
            BOOST_EGG_name(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &&a)) \
            { \
                return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()( \
                    BOOST_PP_ENUM(N, BOOST_EGG_EXPLICIT_fwd, A) \
                ); \
            } \
        /**/

        #define BOOST_EGG_EXPLICIT_fwd(Z, N, A) boost::egg::std_forward<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))


#else


    #include <boost/preprocessor/array/elem.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/tuple/eat.hpp>
    #include <boost/egg/detail/boost_workaround.hpp>
    #include <boost/egg/preprocessor/bits_enum_binary_params.hpp>
    #include <boost/egg/preprocessor/for_each_bits.hpp>


    #define BOOST_EGG_EXPLICIT(N, Name, X_, Params) \
        BOOST_EGG_PP_FOR_EACH_BITS(N, BOOST_EGG_EXPLICIT_op, (3, (Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params)))) \
    /**/


    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

        #include <boost/egg/detail/vc7_1_result_of.hpp>
        #include <boost/egg/preprocessor/bits_enum.hpp>

        #define BOOST_EGG_EXPLICIT_op(R, Bits, Nm_X_P) \
            template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), class A)> \
            typename boost::egg::vc7_1_detail::BOOST_PP_CAT(result_of, BOOST_PP_SEQ_SIZE(Bits))< \
                BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>, \
                BOOST_EGG_PP_BITS_ENUM_R(R, Bits, BOOST_EGG_EXPLICIT_op_w0, BOOST_EGG_EXPLICIT_op_w1, ~) \
            >::type \
            BOOST_PP_ARRAY_ELEM(0, Nm_X_P)(BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, &a)) \
            { \
                return BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>()( \
                    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), a) \
                ); \
            } \
        /**/

        #define BOOST_EGG_EXPLICIT_op_w0(R, I, _) BOOST_PP_CAT(A, I) &
        #define BOOST_EGG_EXPLICIT_op_w1(R, I, _) boost::egg::vc7_1_detail::const_ref<BOOST_PP_CAT(A, I)>

    #else

        #include <boost/preprocessor/facilities/intercept.hpp>
        #include <boost/egg/detail/const_overloaded.hpp>
        #include <boost/egg/preprocessor/for_each_bits.hpp>
        #include <boost/egg/result_of.hpp>

        #define BOOST_EGG_EXPLICIT_op(R, Bits, Nm_X_P) \
            template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), class A)> \
            typename boost::egg::result_of_< \
                BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>( \
                    BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, & BOOST_PP_INTERCEPT) \
                ) \
            >::type \
            BOOST_PP_ARRAY_ELEM(0, Nm_X_P)(BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, &a) BOOST_EGG_CONST_OVERLOADED_PARAMS(BOOST_PP_SEQ_SIZE(Bits), A)) \
            { \
                return BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>()( \
                    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), a) \
                ); \
            } \
        /**/

    #endif // BOOST_WORKAROUND(BOOST_MSVC, == 1310)


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#endif
