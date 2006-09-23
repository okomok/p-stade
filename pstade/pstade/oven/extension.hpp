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
struct extension;


namespace extension_detail {


    template< class T >
    struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename extension<plain_t>::template meta<plain_t>::mutable_iterator type;
    };


    template< class T >
    struct range_const_iterator
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename extension<plain_t>::template meta<plain_t>::constant_iterator type;
    };


    template< class T >
    struct range_result_iterator :
        boost::mpl::eval_if< boost::is_const<typename boost::remove_reference<T>::type>,
            range_const_iterator<T>,
            PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<T>
        >
    { };


    struct baby_begin
    {
        template< class Unused, class T >
        struct apply :
            range_result_iterator<T>
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
            range_result_iterator<T>
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
    struct range_size
    {
        typedef typename range_result_iterator<T>::type miter_t;
        typedef typename boost::iterator_difference<miter_t>::type type;
    };

    struct baby_size
    {
        template< class Unused, class T >
        struct apply :
            range_size<T>
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

        #define PSTADE_OVEN_EXTENSION_namespace_open_op(R, _, Elem) \
            namespace Elem { \
        /**/


    #define PSTADE_OVEN_EXTENSION_namespace_close(NamespaceList) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_close_op, ~, NamespaceList) \
    /**/

        #define PSTADE_OVEN_EXTENSION_namespace_close_op(R, _, Elem) \
            } \
        /**/


    #define PSTADE_OVEN_EXTENSION_namespace_expand_op(R, _, Elem) \
        :: Elem \
    /**/


#define PSTADE_OVEN_EXTENSION_TYPE(NamespaceList, Name) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NamespaceList, Name, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NamespaceList, Name, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NamespaceList, Name, range_size) \
    } \
    \
    PSTADE_OVEN_EXTENSION_namespace_open(NamespaceList) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NamespaceList, Name, begin, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NamespaceList, Name, end,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NamespaceList, Name, size , range_size) \
    PSTADE_OVEN_EXTENSION_namespace_close(NamespaceList) \
/**/


    #define PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_expand_op, ~, NamespaceList) :: Name \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NamespaceList, Name, Fun) \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) > : \
            pstade::oven::extension_detail::Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) & > : \
            Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) const > : \
            Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) volatile > : \
            Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) const volatile > : \
            Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_forward(NamespaceList, Name, Fun, Result) \
        inline \
        pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) >::type \
        Fun(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name)& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
        \
        inline \
        pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) const >::type \
        Fun(PSTADE_OVEN_EXTENSION_TYPE_fullname(NamespaceList, Name) const& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
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
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NamespaceList, Name, ParamSeq, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NamespaceList, Name, ParamSeq, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NamespaceList, Name, ParamSeq, range_size) \
    } \
    \
    PSTADE_OVEN_EXTENSION_namespace_open(NamespaceList) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NamespaceList, Name, ParamSeq, begin, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NamespaceList, Name, ParamSeq, end,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NamespaceList, Name, ParamSeq, size , range_size) \
    PSTADE_OVEN_EXTENSION_namespace_close(NamespaceList) \
/**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) \
        BOOST_PP_SEQ_FOR_EACH_I(PSTADE_OVEN_EXTENSION_TEMPLATE_params_op, ~, ParamSeq) \
    /**/

        #define PSTADE_OVEN_EXTENSION_TEMPLATE_params_op(R, _, I, Elem) \
            BOOST_PP_COMMA_IF(I) Elem BOOST_PP_CAT(T, I) \
        /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) \
        BOOST_PP_LIST_FOR_EACH(PSTADE_OVEN_EXTENSION_namespace_expand_op, ~, NamespaceList) \
        :: Name < BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) > \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NamespaceList, Name, ParamSeq, Fun) \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq)& > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) > \
        { }; \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) const > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) > \
        { }; \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) volatile > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) > \
        { }; \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) const volatile > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NamespaceList, Name, ParamSeq, Fun, Result) \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > inline \
        typename pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) >::type \
        Fun(PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq)& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > inline \
        typename pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) const >::type \
        Fun(PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NamespaceList, Name, ParamSeq) const& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


#endif
