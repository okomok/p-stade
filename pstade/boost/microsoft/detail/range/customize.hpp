#ifndef BOOST_MICROSOFT_DETAIL_RANGE_CUSTOMIZE_HPP
#define BOOST_MICROSOFT_DETAIL_RANGE_CUSTOMIZE_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// See: BOOST_TYPEOF_TOSEQ of <boost/typeof/template_encoding.hpp>
//
// Copyright (C) 2004 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size_type.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <boost/version.hpp>

#include <boost/microsoft/detail/range/customize_fwd.hpp>


namespace boost { namespace microsoft { namespace range_customize {


namespace detail {


    template< class T >
    struct bare :
        remove_cv<typename remove_reference<T>::type>
    { };


    template< class T >
    struct tag_of :
        tag<typename detail::bare<T>::type>
    { };


    template< class T >
    struct metafunctions_of
    {
        typedef metafunctions<
            typename tag_of<T>::type,
            typename bare<T>::type
        > type;
    };


    template< class T >
    struct functions_of
    {
        typedef functions<typename tag_of<T>::type> type;
    };


} // namespace detail


// helpers, never apply these to non-dependent names!
//
template< class T >
struct mutable_iterator
{
private:
    typedef typename detail::metafunctions_of<T>::type mf_t;

public:
    typedef typename mf_t::mutable_iterator type;
};


template< class T >
struct const_iterator
{
private:
    typedef typename detail::metafunctions_of<T>::type mf_t;

public:
    typedef typename mf_t::const_iterator type;
};


template< class T >
struct size_type
{
private:
    typedef typename detail::metafunctions_of<T>::type mf_t;

public:
    typedef typename mf_t::size_type type;
};


template< class T >
struct iterator
{
private:
    typedef typename detail::metafunctions_of<T>::type mf_t;

public:
    typedef typename mpl::if_< is_const<T>,
        typename mf_t::const_iterator,
        typename mf_t::mutable_iterator
    >::type type;
};


// utilities
//
template< class Result, class T >
struct overloaded :
    boost::disable_if< boost::is_const<T>, Result >
{ };


} } } // namespace boost::microsoft::range_customize


#if !(BOOST_VERSION > 103301)
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_legacy_way
#endif


#if !defined(BOOST_MICROSOFT_RANGE_CUSTOMIZE_legacy_way)
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_begin    range_begin
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_end      range_end
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_iterator       range_mutable_iterator
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_const_iterator range_const_iterator
#else
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_begin    boost_range_begin
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_end      boost_range_end
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_size     boost_range_size
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_iterator       range_iterator
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_const_iterator range_const_iterator
    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_size           range_size
#endif


#define BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_open(NamespaceList) \
    BOOST_PP_LIST_FOR_EACH(BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_open_op, ~, NamespaceList) \
/**/

    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_open_op(r, data, elem) \
        namespace elem { \
    /**/


#define BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_close(NamespaceList) \
    BOOST_PP_LIST_FOR_EACH(BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_close_op, ~, NamespaceList) \
/**/

    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_close_op(r, data, elem) \
        } \
    /**/


#define BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_expand_op(r, data, elem) \
    :: elem \
/**/


#define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(Tag, NamespaceList, Name) \
    namespace boost { namespace microsoft { namespace range_customize { \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_tag(Tag, BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
    } } } \
    \
    namespace boost { \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_iterator(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_const_iterator(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_size_type(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
    } \
    \
    BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_open(NamespaceList) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_begin(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_begin_const(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_end(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_end_const(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_size(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name)) \
    BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_close(NamespaceList) \
/**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_fullname(NamespaceList, Name) \
        BOOST_PP_LIST_FOR_EACH(BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_expand_op, ~, NamespaceList) :: Name \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_tag(Tag, Fullname) \
        template< > \
        struct tag< Fullname > \
        { \
            typedef Tag type; \
        }; \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_iterator(Fullname) \
        template< > \
        struct BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_iterator< Fullname > \
        { \
            typedef microsoft::range_customize::detail::metafunctions_of< Fullname >::type mf_t; \
            typedef mf_t::mutable_iterator type; \
        }; \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_const_iterator(Fullname) \
        template< > \
        struct BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_const_iterator< Fullname > \
        { \
            typedef microsoft::range_customize::detail::metafunctions_of< Fullname >::type mf_t; \
            typedef mf_t::const_iterator type; \
        }; \
    /**/


    #if !defined(BOOST_MICROSOFT_RANGE_CUSTOMIZE_legacy_way)

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_size_type(Fullname) \
        /**/

    #else

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_size_type(Fullname) \
            template< > \
            struct BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_size< Fullname > \
            { \
                typedef microsoft::range_customize::detail::metafunctions_of< Fullname >::type mf_t; \
                typedef mf_t::size_type type; \
            }; \
        /**/

    #endif


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_begin(Fullname) \
        inline \
        boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_begin(Fullname& x) \
        { \
            typedef boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().begin< \
                boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_begin_const(Fullname) \
        inline \
        boost::microsoft::range_customize::const_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_begin(const Fullname& x) \
        { \
            typedef boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().begin< \
                boost::microsoft::range_customize::const_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_end(Fullname) \
        inline \
        boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_end(Fullname& x) \
        { \
            typedef boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().end< \
                boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_end_const(Fullname) \
        inline \
        boost::microsoft::range_customize::const_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_end(const Fullname& x) \
        { \
            typedef boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().end< \
                boost::microsoft::range_customize::const_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #if !defined(BOOST_MICROSOFT_RANGE_CUSTOMIZE_legacy_way)

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_size(Fullname) \
        /**/

    #else

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE_size(Fullname) \
            inline \
            boost::microsoft::range_customize::size_type< Fullname >::type \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_size(const Fullname& x) \
            { \
                typedef boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
                return f_t().size< \
                    boost::microsoft::range_customize::size_type< Fullname >::type \
                >(x); \
            } \
        /**/

    #endif


#define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(Tag, NamespaceList, Name, ParamSeqOrCount) \
    BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_impl( \
        Tag, NamespaceList, Name, \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_to_param_seq(ParamSeqOrCount) \
    ) \
/**/

    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_to_param_seq(ParamSeqOrCount) \
        BOOST_PP_IIF(BOOST_PP_IS_UNARY(ParamSeqOrCount), \
            ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
            BOOST_PP_REPEAT \
        )(ParamSeqOrCount, BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_to_param_seq_op, ~) \
    /**/

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_to_param_seq_op(z, n, _) \
            (class) \
        /**/


#define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_impl(Tag, NamespaceList, Name, ParamSeq) \
    namespace boost { namespace microsoft { namespace range_customize { \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_tag( \
            Tag, \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    } } } \
    \
    namespace boost { \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_iterator( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_const_iterator( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_size_type( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    } \
    \
    BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_open(NamespaceList) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_begin( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_begin_const( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_end( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_end_const( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_size( \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq), \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_close(NamespaceList) \
/**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params(ParamSeq) \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params_op, ~, ParamSeq) \
    /**/

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_params_op(r, data, i, elem) \
            BOOST_PP_COMMA_IF(i) elem BOOST_PP_CAT(T, i) \
        /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        BOOST_PP_LIST_FOR_EACH(BOOST_MICROSOFT_RANGE_CUSTOMIZE_namespace_expand_op, ~, NamespaceList) \
        :: Name < BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) > \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_tag(Tag, Params, Fullname) \
        template< Params > \
        struct tag< Fullname > \
        { \
            typedef Tag type; \
        }; \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_iterator(Params, Fullname) \
        template< Params > \
        struct BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_iterator< Fullname > \
        { \
            typedef typename microsoft::range_customize::detail::metafunctions_of< Fullname >::type mf_t; \
            typedef typename mf_t::mutable_iterator type; \
        }; \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_const_iterator(Params, Fullname) \
        template< Params > \
        struct BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_const_iterator< Fullname > \
        { \
            typedef typename microsoft::range_customize::detail::metafunctions_of< Fullname >::type mf_t; \
            typedef typename mf_t::const_iterator type; \
        }; \
    /**/


    #if !defined(BOOST_MICROSOFT_RANGE_CUSTOMIZE_legacy_way)

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_size_type(Params, Fullname) \
        /**/

    #else

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_size_type(Params, Fullname) \
            template< Params > \
            struct BOOST_MICROSOFT_RANGE_CUSTOMIZE_range_size< Fullname > \
            { \
                typedef typename microsoft::range_customize::detail::metafunctions_of< Fullname >::type mf_t; \
                typedef typename mf_t::size_type type; \
            }; \
        /**/

    #endif


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_begin(Params, Fullname) \
        template< Params > inline \
        typename boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_begin(Fullname& x) \
        { \
            typedef typename boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().template begin< \
                typename boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_begin_const(Params, Fullname) \
        template< Params > inline \
        typename boost::microsoft::range_customize::const_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_begin(const Fullname& x) \
        { \
            typedef typename boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().template begin< \
                typename boost::microsoft::range_customize::const_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_end(Params, Fullname) \
        template< Params > inline \
        typename boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_end(Fullname& x) \
        { \
            typedef typename boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().template end< \
                typename boost::microsoft::range_customize::mutable_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_end_const(Params, Fullname) \
        template< Params > inline \
        typename boost::microsoft::range_customize::const_iterator< Fullname >::type \
        BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_end(const Fullname& x) \
        { \
            typedef typename boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
            return f_t().template end< \
                typename boost::microsoft::range_customize::const_iterator< Fullname >::type \
            >(x); \
        } \
    /**/


    #if !defined(BOOST_MICROSOFT_RANGE_CUSTOMIZE_legacy_way)

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_size(Params, Fullname) \
        /**/

    #else

        #define BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE_size(Params, Fullname) \
            template< Params > inline \
            typename boost::microsoft::range_customize::size_type< Fullname >::type \
            BOOST_MICROSOFT_RANGE_CUSTOMIZE_boost_range_size(const Fullname& x) \
            { \
                typedef typename boost::microsoft::range_customize::detail::functions_of< Fullname >::type f_t; \
                return f_t().template size< \
                    typename boost::microsoft::range_customize::size_type< Fullname >::type \
                >(x); \
            } \
        /**/

    #endif


#endif
