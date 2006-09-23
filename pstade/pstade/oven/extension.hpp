#ifndef PSTADE_OVEN_EXTENSION_HPP
#define PSTADE_OVEN_EXTENSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp> // iterator_difference
#include <boost/mpl/eval_if.hpp>
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
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/remove_cvr.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_BEGIN etc.
#include "./distance.hpp"


namespace pstade { namespace oven {


template< class T, class Active = void >
struct extension; /*
{
    // example

    template< class X >
    struct meta
    {
        typedef int *mutable_iterator;
        typedef int const *constant_iterator;
    };

    template< class Iterator, class X >
    const_overloaded<Iterator, X>::type begin(X& x)
    {
        return x.first;
    }

    template< class Iterator, class X >
    Iterator begin(X const& x)
    {
        return x.cfirst;
    }

    template< class Iterator, class X >
    Iterator end(X& x)
    {
        return x.last;
    }
}; */


namespace extension_detail {


    template< class T >
    struct mutable_iterator
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename extension<plain_t>::template meta<plain_t>::mutable_iterator type;
    };


    template< class T >
    struct constant_iterator
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename extension<plain_t>::template meta<plain_t>::constant_iterator type;
    };


    template< class T >
    struct result_iterator :
        boost::mpl::eval_if< boost::is_const<typename boost::remove_reference<T>::type>,
            constant_iterator<T>,
            mutable_iterator<T>
        >
    { };


    struct baby_begin
    {
        template< class Unused, class T >
        struct apply :
            result_iterator<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            typedef typename boost::remove_cv<T>::type plain_t;
            return extension<plain_t>().template begin<Result>(x);
        }
    };

    PSTADE_EGG_FUNCTION(begin, baby_begin)


    struct baby_end
    {
        template< class Unused, class T >
        struct apply :
            result_iterator<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            typedef typename boost::remove_cv<T>::type plain_t;
            return extension<plain_t>().template end<Result>(x);
        }
    };

    PSTADE_EGG_FUNCTION(end, baby_end)


    template< class T >
    struct result_of_size
    {
        typedef typename mutable_iterator<T>::type miter_t;
        typedef typename boost::iterator_difference<miter_t>::type type;
    };

    struct baby_size
    {
        template< class Unused, class T >
        struct apply :
            result_of_size<T>
        { };

        template< class Result, class T >
        Result call(T const& x)
        {
            return oven::distance(x);
        }
    };

    PSTADE_EGG_FUNCTION(size, baby_size)


} // namespace extension_detail


} } // namespace pstade::oven


// Bridge macros between Oven and Boost.Range Extension
//

    #define PSTADE_OVEN_EXTENSION_namespace_open(NamespaceList) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_open_op, ~, NamespaceList) \
    /**/

        #define PSTADE_OVEN_EXTENSION_namespace_open_op(r, data, elem) \
            namespace elem { \
        /**/


    #define PSTADE_OVEN_EXTENSION_namespace_close(NamespaceList) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_close_op, ~, NamespaceList) \
    /**/

        #define PSTADE_OVEN_EXTENSION_namespace_close_op(r, data, elem) \
            } \
        /**/


    #define PSTADE_OVEN_EXTENSION_namespace_expand_op(r, data, elem) \
        :: elem \
    /**/


#define PSTADE_OVEN_EXTENSION_TYPE(NamespaceList, Name) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TYPE_mutable_iterator(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
        PSTADE_OVEN_EXTENSION_TYPE_const_iterator(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
        PSTADE_OVEN_EXTENSION_TYPE_size_type(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
    } \
    \
    PSTADE_OVEN_EXTENSION_namespace_open(NamespaceList) \
        PSTADE_OVEN_EXTENSION_TYPE_begin(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
        PSTADE_OVEN_EXTENSION_TYPE_begin_const(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
        PSTADE_OVEN_EXTENSION_TYPE_end(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
        PSTADE_OVEN_EXTENSION_TYPE_end_const(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
        PSTADE_OVEN_EXTENSION_TYPE_size(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)) \
    PSTADE_OVEN_EXTENSION_namespace_close(NamespaceList) \
/**/

    #define PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_expand_op, ~, NamespaceList) :: Name \
    /**/


    // metafunctions
    //

    #define PSTADE_OVEN_EXTENSION_TYPE_mutable_iterator(Fullname) \
        template< > \
        struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< Fullname > : \
            pstade::oven::extension_detail::mutable_iterator< Fullname > \
        { }; \
        template< > \
        struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< Fullname const > : \
            PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< Fullname > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_const_iterator(Fullname) \
        template< > \
        struct range_const_iterator< Fullname > : \
            pstade::oven::extension_detail::constant_iterator< Fullname > \
        { }; \
        \
        template< > \
        struct range_const_iterator< Fullname const > : \
            range_const_iterator< Fullname > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_size_type(Fullname) \
        template< > \
        struct range_size< Fullname > : \
            pstade::oven::extension_detail::result_of_size< Fullname > \
        { }; \
        template< > \
        struct range_size< Fullname const > : \
            range_size< Fullname > \
        { }; \
    /**/


    // functions
    //

    #define PSTADE_OVEN_EXTENSION_TYPE_begin(Fullname) \
        inline \
        pstade::oven::extension_detail::result_iterator< Fullname >::type \
        PSTADE_OVEN_BOOST_RANGE_BEGIN(Fullname& x) \
        { \
            return pstade::oven::extension_detail::begin(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_begin_const(Fullname) \
        inline \
        pstade::oven::extension_detail::result_iterator< Fullname const >::type \
        PSTADE_OVEN_BOOST_RANGE_BEGIN(Fullname const& x) \
        { \
            return pstade::oven::extension_detail::begin(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_end(Fullname) \
        inline \
        pstade::oven::extension_detail::result_iterator< Fullname >::type \
        PSTADE_OVEN_BOOST_RANGE_END(Fullname& x) \
        { \
            return pstade::oven::extension_detail::end(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_end_const(Fullname) \
        inline \
        pstade::oven::extension_detail::result_iterator< Fullname const >::type \
        PSTADE_OVEN_BOOST_RANGE_END(Fullname const& x) \
        { \
            return pstade::oven::extension_detail::end(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_size(Fullname) \
        inline \
        pstade::oven::extension_detail::result_of_size< Fullname >::type \
        boost_range_size(Fullname const& x) \
        { \
            return pstade::oven::extension_detail::size(x); \
        } \
    /**/


#define PSTADE_OVEN_EXTENSION_TEMPLATE(NamespaceList, Name, ParamSeqOrCount) \
    PSTADE_OVEN_EXTENSION_TEMPLATE_impl( \
        NamespaceList, Name, \
        PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq(ParamSeqOrCount) \
    ) \
/**/

    #define PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq(ParamSeqOrCount) \
        BOOST_PP_IIF(BOOST_PP_IS_UNARY(ParamSeqOrCount), \
            ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
            BOOST_PP_REPEAT \
        )(ParamSeqOrCount, PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq_op, ~) \
    /**/

        #define PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq_op(Z, N, _) \
            (class) \
        /**/


#define PSTADE_OVEN_EXTENSION_TEMPLATE_impl(NamespaceList, Name, ParamSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TEMPLATE_mutable_iterator( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_const_iterator( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        \
        PSTADE_OVEN_EXTENSION_TEMPLATE_size_type( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    } \
    \
    PSTADE_OVEN_EXTENSION_namespace_open(NamespaceList) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_begin( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_begin_const( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_end( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_end_const( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_size( \
            PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq), \
            PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        ) \
    PSTADE_OVEN_EXTENSION_namespace_close(NamespaceList) \
/**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) \
        BOOST_PP_SEQ_FOR_EACH_I(PSTADE_OVEN_EXTENSION_TEMPLATE_params_op, ~, ParamSeq) \
    /**/

        #define PSTADE_OVEN_EXTENSION_TEMPLATE_params_op(r, data, i, elem) \
            BOOST_PP_COMMA_IF(i) elem BOOST_PP_CAT(T, i) \
        /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_expand_op, ~, NamespaceList) \
        :: Name < BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) > \
    /**/


    // metafunctions
    //

    #define PSTADE_OVEN_EXTENSION_TEMPLATE_mutable_iterator(Params, Fullname) \
        template< Params > \
        struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< Fullname > : \
            pstade::oven::extension_detail::mutable_iterator< Fullname > \
        { }; \
        template< Params > \
        struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< Fullname const > : \
            pstade::oven::extension_detail::mutable_iterator< Fullname > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_const_iterator(Params, Fullname) \
        template< Params > \
        struct range_const_iterator< Fullname > : \
            pstade::oven::extension_detail::constant_iterator< Fullname > \
        { }; \
        template< Params > \
        struct range_const_iterator< Fullname const > : \
            range_const_iterator< Fullname > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_size_type(Params, Fullname) \
        template< Params > \
        struct range_size< Fullname > : \
            pstade::oven::extension_detail::result_of_size< Fullname > \
        { }; \
        template< Params > \
        struct range_size< Fullname const > : \
            range_size< Fullname > \
        { }; \
    /**/


    // functions
    //

    #define PSTADE_OVEN_EXTENSION_TEMPLATE_begin(Params, Fullname) \
        template< Params > inline \
        typename pstade::oven::extension_detail::result_iterator< Fullname >::type \
        PSTADE_OVEN_BOOST_RANGE_BEGIN(Fullname& x) \
        { \
            return pstade::oven::extension_detail::begin(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_begin_const(Params, Fullname) \
        template< Params > inline \
        typename pstade::oven::extension_detail::result_iterator< Fullname const >::type \
        PSTADE_OVEN_BOOST_RANGE_BEGIN(Fullname const& x) \
        { \
            return pstade::oven::extension_detail::begin(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_end(Params, Fullname) \
        template< Params > inline \
        typename pstade::oven::extension_detail::result_iterator< Fullname >::type \
        PSTADE_OVEN_BOOST_RANGE_END(Fullname& x) \
        { \
            return pstade::oven::extension_detail::end(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_end_const(Params, Fullname) \
        template< Params > inline \
        typename pstade::oven::extension_detail::result_iterator< Fullname const >::type \
        PSTADE_OVEN_BOOST_RANGE_END(Fullname const& x) \
        { \
            return pstade::oven::extension_detail::end(x); \
        } \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_size(Params, Fullname) \
        template< Params > inline \
        typename pstade::oven::extension_detail::result_of_size< Fullname >::type \
        boost_range_size(Fullname const& x) \
        { \
            return pstade::oven::extension_detail::size(x); \
        } \
    /**/


#endif
