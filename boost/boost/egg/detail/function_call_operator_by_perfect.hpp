#ifndef BOOST_EGG_DETAIL_FUNCTION_CALL_OPERATOR_BY_PERFECT_HPP
#define BOOST_EGG_DETAIL_FUNCTION_CALL_OPERATOR_BY_PERFECT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS


#if defined(BOOST_EGG_HAS_RVALUE_REFS)


    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/egg/preprocessor/enum_template_params.hpp>


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(N, Cv) \
        BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS(N, class A) \
        typename apply_little< \
            little_type Cv() \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename remove_reference<A, >::type BOOST_PP_INTERCEPT) \
        >::type \
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &&a)) Cv() \
        { \
            return call_little(this->little() BOOST_PP_ENUM_TRAILING_PARAMS(N, a)); \
        } \
    /**/


#else


    #include <boost/preprocessor/control/if.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/tuple/eat.hpp>
    #include <boost/egg/preprocessor/bits_enum_binary_params.hpp>
    #include <boost/egg/preprocessor/bits_enum_deduced.hpp>
    #include <boost/egg/preprocessor/for_each_bits.hpp>


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(N, Cv) \
        BOOST_PP_IF( N, \
            BOOST_EGG_PP_FOR_EACH_BITS, \
            BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT0(Cv) BOOST_PP_TUPLE_EAT(3) \
        )(BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_op, Cv, N) \
    /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT0(Cv) \
            typename apply_little<little_type Cv()>::type \
            operator()() Cv() \
            { \
                return call_little(this->little()); \
            } \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_op(R, Bits, Cv) \
            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), class A)> \
            typename apply_little<little_type Cv(), BOOST_EGG_PP_BITS_ENUM_DEDUCED_R(R, Bits, A)>::type \
            operator()(BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, &a)) Cv() \
            { \
                return call_little(this->little(), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), a)); \
            } \
        /**/


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#endif
