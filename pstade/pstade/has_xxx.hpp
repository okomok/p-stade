#ifndef PSTADE_HAS_XXX_HPP
#define PSTADE_HAS_XXX_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/spirit/phoenix/stl/container/detail/container.hpp>
// http://lists.boost.org/Archives/boost/2002/03/27251.php
// http://lists.boost.org/Archives/boost/2004/11/75621.php
// http://lists.boost.org/Archives/boost/2003/11/56173.php
// http://groups.google.com/group/comp.lang.c++.moderated/msg/4824b231db71ad08


// What:
//
// Replaces 'BOOST_MPL_HAS_XXX_TRAIT_DEF' for the workaround of
// http://lists.boost.org/Archives/boost/2005/10/95809.php
// http://svn.boost.org/trac/boost/ticket/1317


#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <pstade/boost_workaround.hpp>
#include <pstade/nullptr.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1
    #define PSTADE_HAS_XXX_TYPE_AND_DATA_NAME_CONFUSION
#endif


#define PSTADE_HAS_TYPE(Type) \
    PSTADE_HAS_TYPE_NAMED(BOOST_PP_CAT(has_, Type), Type) \
/**/


#define PSTADE_HAS_TYPE_NAMED(Name, Type) \
    PSTADE_HAS_type(Name, Type) \
/**/


    #define PSTADE_HAS_type(Name, Type) \
        namespace PSTADE_HAS_helper_ns_of(Name) { \
            \
            template< class T > \
            boost::type_traits::yes_type test(typename T::Type (*)()); \
            \
            template< class T > \
            boost::type_traits::no_type  test(...); \
            \
        } \
        \
        template< class T > \
        struct Name : \
            boost::mpl::bool_< \
                sizeof( PSTADE_HAS_helper_ns_of(Name)::test<T>(PSTADE_NULLPTR) ) \
                    == sizeof(boost::type_traits::yes_type) \
            > \
        { }; \
    /**/


    #define PSTADE_HAS_helper_ns_of(Name) \
        BOOST_PP_CAT(pstade_has_xxx_helper_, Name) \
    /**/


#if !defined(PSTADE_HAS_XXX_TYPE_AND_DATA_NAME_CONFUSION)


    #define PSTADE_HAS_DATA(Type, Var) \
        PSTADE_HAS_DATA_NAMED(BOOST_PP_CAT(has_, Var), Type, Var) \
    /**/


    #define PSTADE_HAS_DATA_NAMED(Name, Type, Var) \
        PSTADE_HAS_data(Name, Type, Var) \
    /**/


#else // God bless you.


    #define PSTADE_HAS_DATA(Type, Var) \
        PSTADE_HAS_DATA_NAMED(BOOST_PP_CAT(has_, Var), Type, Var) \
    /**/


    #define PSTADE_HAS_DATA_NAMED(Name, Type, Var) \
        PSTADE_HAS_type(BOOST_PP_CAT(pstade_has_type_, Name), Var) \
        PSTADE_HAS_data(BOOST_PP_CAT(pstade_has_data_impl_, Name), Type, Var) \
        \
        template< class T > \
        struct Name : \
            boost::mpl::eval_if< BOOST_PP_CAT(pstade_has_type_, Name)<T>, \
                boost::mpl::false_, \
                BOOST_PP_CAT(pstade_has_data_impl_, Name)<T> \
            > \
        { }; \
    /**/


#endif // !defined(PSTADE_HAS_XXX_TYPE_AND_DATA_NAME_CONFUSION)


    #define PSTADE_HAS_data(Name, Type, Var) \
        namespace PSTADE_HAS_helper_ns_of(Name) { \
            \
            template< class T, Type T::* > \
            struct holder \
            { }; \
            \
            template< class T > \
            boost::type_traits::yes_type test(holder<T, &T::Var> *); \
            \
            template< class T > \
            boost::type_traits::no_type  test(...); \
            \
        } \
        \
        template< class T > \
        struct Name : \
            boost::mpl::bool_< \
                sizeof( PSTADE_HAS_helper_ns_of(Name)::test<T>(PSTADE_NULLPTR) ) \
                    == sizeof(boost::type_traits::yes_type) \
            > \
        { }; \
    /**/


#if !defined(PSTADE_HAS_XXX_TYPE_AND_DATA_NAME_CONFUSION)


    #define PSTADE_HAS_FUNCTION(Result, Fun, ParamSeq) \
        PSTADE_HAS_FUNCTION_NAMED(BOOST_PP_CAT(has_, Fun), Result, Fun, ParamSeq) \
    /**/


    #define PSTADE_HAS_FUNCTION_NAMED(Name, Result, Fun, ParamSeq) \
        PSTADE_HAS_function(Name, Result, Fun, ParamSeq) \
    /**/


#else // God bless you.


    #define PSTADE_HAS_FUNCTION(Result, Fun, ParamSeq) \
        PSTADE_HAS_FUNCTION_NAMED(BOOST_PP_CAT(has_, Fun), Result, Fun, ParamSeq) \
    /**/


    #define PSTADE_HAS_FUNCTION_NAMED(Name, Result, Fun, ParamSeq) \
        PSTADE_HAS_type(BOOST_PP_CAT(pstade_has_type_, Name), Fun) \
        PSTADE_HAS_function(BOOST_PP_CAT(pstade_has_function_impl_, Name), Result, Fun, ParamSeq) \
        \
        template< class T > \
        struct Name : \
            boost::mpl::eval_if< BOOST_PP_CAT(pstade_has_type_, Name)<T>, \
                boost::mpl::false_, \
                BOOST_PP_CAT(pstade_has_function_impl_, Name)<T> \
            > \
        { }; \
    /**/


#endif // !defined(PSTADE_HAS_XXX_TYPE_AND_DATA_NAME_CONFUSION)


    #define PSTADE_HAS_function(Name, Result, Fun, ParamSeq) \
        namespace PSTADE_HAS_helper_ns_of(Name) { \
            \
            template< class T, Result (T::*)(BOOST_PP_SEQ_ENUM(ParamSeq)) > \
            struct holder \
            { }; \
            \
            template< class T > \
            boost::type_traits::yes_type test(holder<T, &T::Fun> *); \
            \
            template< class T > \
            boost::type_traits::no_type  test(...); \
            \
        } \
        \
        template< class T > \
        struct Name : \
            boost::mpl::bool_< \
                sizeof( PSTADE_HAS_helper_ns_of(Name)::test<T>(PSTADE_NULLPTR) ) \
                    == sizeof(boost::type_traits::yes_type) \
            > \
        { }; \
    /**/


#endif
