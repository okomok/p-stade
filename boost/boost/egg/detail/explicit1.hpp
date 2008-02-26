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
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/const_overloaded.hpp>


#define BOOST_EGG_EXPLICIT1(Name, X_, Params) \
    BOOST_EGG_EXPLICIT1_aux(Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params)) \
/**/


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)


    #define BOOST_EGG_EXPLICIT1_aux(Name, X_, Params) \
        \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), class A> inline \
        typename boost::egg::result_of_<X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>(A &)>::type \
        Name(A &a BOOST_EGG_CONST_OVERLOADED1(A)) \
        { \
            return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()(a); \
        } \
        \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), class A> inline \
        typename boost::egg::details::result_of1_cref<X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>, A>::type \
        Name(A const &a) \
        { \
            return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()(a); \
        } \
        \
    /**/


    namespace boost { namespace egg { namespace details {


        // add_const is needed to work around array bug (see "deduced_const.hpp"),
        // but once it is placed in namespace scope result_of, it sometimes fails to const-qualify.
        // So that, it must be delayed without add_const to const-qualify.
        template<class Fun, class A>
        struct result_of1_cref :
            result_of_<Fun(A const &)>
        { };


    } } } // namespace boost::egg::details


#else


    #define BOOST_EGG_EXPLICIT1_aux(Name, X_, Params) \
        \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), class A> inline \
        typename boost::egg::result_of_<X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>(A &)>::type \
        Name(A &a BOOST_EGG_CONST_OVERLOADED1(A)) \
        { \
            return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()(a); \
        } \
        \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), class A> inline \
        typename boost::egg::result_of_<X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>(A const &)>::type \
        Name(A const &a) \
        { \
            return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()(a); \
        } \
        \
    /**/


#endif // BOOST_WORKAROUND(BOOST_MSVC, == 1310)


#endif
