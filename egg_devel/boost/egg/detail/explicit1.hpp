#ifndef BOOST_EGG_DETAIL_EXPLICIT1_HPP
#define BOOST_EGG_DETAIL_EXPLICIT1_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/seq_enum_args.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>
#include <boost/egg/preprocessor/to_template_param_seq.hpp>
#include <boost/egg/detail/const_overloaded1.hpp>
#include <boost/egg/detail/ns_result_of1.hpp>


#define BOOST_EGG_EXPLICIT1(Name, X_, Params) \
    BOOST_EGG_EXPLICIT1_aux(Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params)) \
/**/

    #define BOOST_EGG_EXPLICIT1_aux(Name, X_, Params) \
        \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), class A> inline \
        BOOST_EGG_NS_RESULT_OF1((X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>), A &) \
        Name(A &a BOOST_EGG_CONST_OVERLOADED1(A)) \
        { \
            return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()(a); \
        } \
        \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), class A> inline \
        BOOST_EGG_NS_RESULT_OF1((X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>), BOOST_EGG_NS_CONST_REF(A)) \
        Name(A const &a) \
        { \
            return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()(a); \
        } \
        \
    /**/


#endif
