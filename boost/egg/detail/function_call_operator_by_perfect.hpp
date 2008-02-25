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


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(N) \
        BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS(N, class A) \
        typename apply_little< \
            little_type const \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename remove_reference<A, >::type BOOST_PP_INTERCEPT) \
        >::type \
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &&a)) const \
        { \
            return call_little(this->little() BOOST_PP_ENUM_TRAILING_PARAMS(N, a)); \
        } \
    /**/


#else


    #include <boost/preprocessor/control/if.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/seq/enum.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/tuple/eat.hpp>
    #include <boost/egg/preprocessor/for_each_by_perfect.hpp>
    #include <boost/egg/preprocessor/seq_enum_params.hpp>


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(N, Cv) \
        BOOST_PP_IF( N, \
            BOOST_EGG_PP_FOR_EACH_BY_PERFECT, \
            BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT0(Cv) BOOST_PP_TUPLE_EAT(4) \
        )(N, A, BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_op, Cv) \
    /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT0(Cv) \
            typename apply_little<little_type Cv>::type \
            operator()() Cv \
            { \
                return call_little(this->little()); \
            } \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_op(R, Cv, Qs, Rs) \
            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Qs), class A)> \
            typename apply_little<little_type Cv, BOOST_PP_SEQ_ENUM(Qs)>::type \
            operator()(BOOST_EGG_PP_SEQ_ENUM_PARAMS(Rs, a)) Cv \
            { \
                return call_little(this->little(), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Qs), a)); \
            } \
        /**/


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#endif
