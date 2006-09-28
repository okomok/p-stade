#ifndef PSTADE_OVEN_EXTENSION_HPP
#define PSTADE_OVEN_EXTENSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp> // iterator_difference
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/remove_cvr.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_BEGIN etc.
#include "./distance.hpp"


namespace pstade_oven_extension {


    struct iter_copyable
    {
        template< class X, class Range >
        X copy(Range& rng)
        {
            return X(boost::begin(rng), boost::end(rng));
        }
    };


    template< class T, class Active = void >
    struct range :
        iter_copyable
    { };


    struct noncopyable
    {
    private:
        template< class X, class Range >
        X copy(Range& rng);
    };


} // namespace pstade_oven_extension


namespace pstade { namespace oven { namespace extension_detail {


    template< class T >
    struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename pstade_oven_extension::range<plain_t>::template meta<plain_t>::mutable_iterator type;
    };


    template< class T >
    struct range_const_iterator
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename pstade_oven_extension::range<plain_t>::template meta<plain_t>::constant_iterator type;
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
            return pstade_oven_extension::range<plain_t>().template begin<Result>(x);
        }
    };

    PSTADE_EGG_FUNCTION(PSTADE_OVEN_BOOST_RANGE_BEGIN, baby_begin)


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
            return pstade_oven_extension::range<plain_t>().template end<Result>(x);
        }
    };

    PSTADE_EGG_FUNCTION(PSTADE_OVEN_BOOST_RANGE_END, baby_end)


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

    PSTADE_EGG_FUNCTION(boost_range_size, baby_size)


} } } // namespace pstade::oven::extension_detail


// Bridge macros between Oven and Boost.Range Extension
//

    #define PSTADE_OVEN_EXTENSION_for_each_without_back(Op, NameSeq) \
        BOOST_PP_SEQ_FOR_EACH(Op, ~, BOOST_PP_SEQ_POP_BACK(NameSeq)) \
    /**/


    #define PSTADE_OVEN_EXTENSION_namespace_open(NameSeq) \
        BOOST_PP_IIF( BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(NameSeq), 1), \
            BOOST_PP_TUPLE_EAT(2), \
            PSTADE_OVEN_EXTENSION_for_each_without_back \
        )(PSTADE_OVEN_EXTENSION_namespace_open_op, NameSeq)
    /**/

        #define PSTADE_OVEN_EXTENSION_namespace_open_op(R, _, Elem) \
            namespace Elem { \
        /**/


    #define PSTADE_OVEN_EXTENSION_namespace_close(NameSeq) \
        BOOST_PP_IIF( BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(NameSeq), 1), \
            BOOST_PP_TUPLE_EAT(2), \
            PSTADE_OVEN_EXTENSION_for_each_without_back \
        )(PSTADE_OVEN_EXTENSION_namespace_close_op, NameSeq)
    /**/

        #define PSTADE_OVEN_EXTENSION_namespace_close_op(R, _, Elem) \
            } \
        /**/


    #define PSTADE_OVEN_EXTENSION_scope_op(R, _, Elem) \
        ::Elem \
    /**/


#define PSTADE_OVEN_EXTENSION_TYPE(NameSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, range_size) \
    } \
    \
    PSTADE_OVEN_EXTENSION_namespace_open(NameSeq) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, PSTADE_OVEN_BOOST_RANGE_BEGIN, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, PSTADE_OVEN_BOOST_RANGE_END,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, boost_range_size,              range_size) \
    PSTADE_OVEN_EXTENSION_namespace_close(NameSeq) \
/**/


    #define PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) \
        BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_EXTENSION_scope_op, ~, NameSeq) \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, Fun) \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) > : \
            pstade::oven::extension_detail::Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) & > : \
            Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) const > : \
            Fun< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, Fun, Result) \
        inline \
        pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) >::type \
        Fun(PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq)& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
        \
        inline \
        pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) const >::type \
        Fun(PSTADE_OVEN_EXTENSION_TYPE_fullname(NameSeq) const& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


#define PSTADE_OVEN_EXTENSION_TEMPLATE(NameSeq, ParamSeqOrCount) \
    PSTADE_OVEN_EXTENSION_TEMPLATE_impl( \
        NameSeq, \
        PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq(ParamSeqOrCount) \
    ) \
/**/

    #define PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq(ParamSeqOrCount) \
        BOOST_PP_IIF( BOOST_MPL_PP_IS_SEQ(ParamSeqOrCount), \
            ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
            BOOST_PP_REPEAT \
        )(ParamSeqOrCount, PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq_op, ~) \
    /**/

        #define PSTADE_OVEN_EXTENSION_TEMPLATE_to_param_seq_op(Z, N, _) \
            (class) \
        /**/


#define PSTADE_OVEN_EXTENSION_TEMPLATE_impl(NameSeq, ParamSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, range_size) \
    } \
    \
    PSTADE_OVEN_EXTENSION_namespace_open(NameSeq) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, PSTADE_OVEN_BOOST_RANGE_BEGIN, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, PSTADE_OVEN_BOOST_RANGE_END,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, boost_range_size,              range_size) \
    PSTADE_OVEN_EXTENSION_namespace_close(NameSeq) \
/**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) \
        BOOST_PP_SEQ_FOR_EACH_I(PSTADE_OVEN_EXTENSION_TEMPLATE_params_op, ~, ParamSeq) \
    /**/

        #define PSTADE_OVEN_EXTENSION_TEMPLATE_params_op(R, _, I, Elem) \
            BOOST_PP_COMMA_IF(I) Elem BOOST_PP_CAT(T, I) \
        /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) \
        BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_EXTENSION_scope_op, ~, NameSeq) \
        < BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) > \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, Fun) \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > : \
            pstade::oven::extension_detail::Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > \
        { }; \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) & > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > \
        { }; \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) const > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, Fun, Result) \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > inline \
        typename pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) >::type \
        Fun(PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq)& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
        \
        template< PSTADE_OVEN_EXTENSION_TEMPLATE_params(ParamSeq) > inline \
        typename pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) const >::type \
        Fun(PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) const& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


#endif
