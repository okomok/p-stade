#ifndef BOOST_EGG_EXPLICIT_HPP
#define BOOST_EGG_EXPLICIT_HPP
#include <boost/egg/detail/prefix.hpp>


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
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/egg/detail/const_overloaded.hpp>
    #include <boost/egg/detail/ns_result_of.hpp>
    #include <boost/egg/preprocessor/bits_enum.hpp>
    #include <boost/egg/preprocessor/bits_enum_binary_params.hpp>
    #include <boost/egg/preprocessor/for_each_bits.hpp>


    #define BOOST_EGG_EXPLICIT(N, Name, X_, Params) \
        BOOST_EGG_PP_FOR_EACH_BITS(N, BOOST_EGG_EXPLICIT_op, (3, (Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params)))) \
    /**/


        #define BOOST_EGG_EXPLICIT_op(R, Bits, Nm_X_P) \
            template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), class A)> \
            BOOST_EGG_NS_RESULT_OF( \
                (BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>), \
                (BOOST_PP_SEQ_SIZE(Bits), (BOOST_EGG_PP_BITS_ENUM_R(R, Bits, BOOST_EGG_EXPLICIT_op_w0, BOOST_EGG_EXPLICIT_op_w1, ~))) \
            ) \
            BOOST_PP_ARRAY_ELEM(0, Nm_X_P)(BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, &a) BOOST_EGG_CONST_OVERLOADED(BOOST_PP_SEQ_SIZE(Bits), A)) \
            { \
                return BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>()( \
                    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), a) \
                ); \
            } \
        /**/

        #define BOOST_EGG_EXPLICIT_op_w0(R, I, _) BOOST_PP_CAT(A, I) &
        #define BOOST_EGG_EXPLICIT_op_w1(R, I, _) BOOST_EGG_NS_CONST_REF(BOOST_PP_CAT(A, I))


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#include <boost/egg/detail/suffix.hpp>
#endif
