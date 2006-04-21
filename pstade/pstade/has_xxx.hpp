#ifndef PSTADE_HAS_XXX_HPP
#define PSTADE_HAS_XXX_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
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


// Why not: BOOST_MPL_HAS_XXX_TRAIT_DEF
//
// http://lists.boost.org/Archives/boost/2005/10/95809.php


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>


namespace pstade { namespace has_xxx_detail {


    struct yes { char a[1]; };
    struct non { char a[2]; };


    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // vc7.1
        #define PSTADE_HAS_XXX_TYPE_AND_DATA_NAME_CONFUSION
    #endif


} } // namespace pstade::has_xxx_detail


#define PSTADE_HAS_TYPE(Type) \
    PSTADE_HAS_TYPE_NAMED(BOOST_PP_CAT(has_, Type), Type) \
/**/


#define PSTADE_HAS_TYPE_NAMED(Name, Type) \
    PSTADE_HAS_type(Name, Type) \
/**/


    #define PSTADE_HAS_type(Name, Type) \
        template< class T > \
        struct Name \
        { \
            template< class U > static \
            pstade::has_xxx_detail::yes test(boost::mpl::identity<U> *, typename U::Type (*)() = 0); \
            \
            static \
            pstade::has_xxx_detail::non test(...); \
            \
            static const bool value = \
                sizeof(test((::boost::mpl::identity<T> *)0)) == sizeof(pstade::has_xxx_detail::yes); \
            \
            typedef boost::mpl::bool_<value> type; \
        }; \
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
        template< class T > \
        struct Name \
        { \
            template< class U, Type U::* > \
            struct holder \
            { }; \
            \
            template< class U > static \
            pstade::has_xxx_detail::yes test(boost::mpl::identity<U> *, holder<U, &U::Var> * = 0); \
            \
            static \
            pstade::has_xxx_detail::non test(...); \
            \
            static const bool value = \
                sizeof(test((::boost::mpl::identity<T> *)0)) == sizeof(pstade::has_xxx_detail::yes); \
            \
            typedef boost::mpl::bool_<value> type; \
        }; \
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
        template< class T > \
        struct Name \
        { \
            template< class U, Result (U::*)(BOOST_PP_SEQ_ENUM(ParamSeq)) > \
            struct holder \
            { }; \
            \
            template< class U > static \
            pstade::has_xxx_detail::yes test(boost::mpl::identity<U> *, holder<U, &U::Fun> * = 0); \
            \
            static \
            pstade::has_xxx_detail::non test(...); \
            \
            static const bool value = \
            sizeof(test((::boost::mpl::identity<T> *)0)) == sizeof(pstade::has_xxx_detail::yes); \
            \
            typedef boost::mpl::bool_<value> type; \
        }; \
    /**/


#endif
