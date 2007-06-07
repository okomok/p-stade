#ifndef PSTADE_OVEN_EXTENSION_HPP
#define PSTADE_OVEN_EXTENSION_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] <boost/numeric/functional.hpp>


#include <cstddef> // size_t
#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/mpl/eval_if.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size_type.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include "./detail/config.hpp"

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #include <pstade/copy_construct.hpp>
    #include "./detail/iter_distance.hpp"
#endif


namespace pstade_oven_extension {


    // If it is already a Range, but not CopyableRange,
    // use the following customization point.

    template< class To >
    struct copy_range { };

    template< class To >
    struct copy_range_base { };

    template< class To, class From > inline
    To pstade_oven_(copy_range_base<To>, From& rng)
    {
        return To(boost::begin(rng), boost::end(rng));
    }

    template< class To, class From > inline
    To pstade_oven_(copy_range<To>, From& rng)
    {
        return pstade_oven_extension::pstade_oven_(copy_range_base<To>(), rng);
    }

    template< class To, class From > inline
    To pstade_oven_copy_range(boost::type<To>, From& rng)
    {
        return pstade_oven_(copy_range<To>(), rng);
    }


    struct range_copyable
    {
        template< class X, class From >
        X copy(From& rng)
        {
            return pstade_oven_copy_range(boost::type<X>(), rng);
        }
    };

    struct range_noncopyable
    {
    private:
        template< class X, class From >
        X copy(From& rng);
    };


    template< class T >
    struct Range_tag
    {
        typedef void type;
    };

    template< class T, class EnableIf >
    struct Range_base :
        range_copyable
    { };

    template< class T, class Tag = typename Range_tag<T>::type >
    struct Range :
        Range_base<T, pstade::enabler>
    { };


    using pstade::enable_if;


} // namespace pstade_oven_extension


namespace pstade { namespace oven { namespace extension_detail {


    template< class T >
    struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
    {
        typedef typename boost::remove_const<T>::type plain_t;
        typedef typename pstade_oven_extension::Range<plain_t>::
            BOOST_NESTED_TEMPLATE associate<plain_t>::mutable_iterator type;
    };


    template< class T >
    struct range_const_iterator
    {
        typedef typename boost::remove_const<T>::type plain_t;
        typedef typename pstade_oven_extension::Range<plain_t>::
            BOOST_NESTED_TEMPLATE associate<plain_t>::constant_iterator type;
    };


    template< class T >
    struct range_result_iterator :
        boost::mpl::eval_if< boost::is_const<T>,
            range_const_iterator<T>,
            PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<T>
        >
    { };


    struct op_begin :
        callable<op_begin>
    {
        template< class Myself, class T >
        struct apply :
            range_result_iterator<T>
        { };

        template< class Result, class T >
        Result call(T& x) const
        {
            typedef typename boost::remove_const<T>::type plain_t;
            return pstade_oven_extension::Range<plain_t>().BOOST_NESTED_TEMPLATE begin<Result>(x);
        }
    };

    PSTADE_CONSTANT(PSTADE_OVEN_BOOST_RANGE_BEGIN, (op_begin))


    struct op_end :
        callable<op_end>
    {
        template< class Myself, class T >
        struct apply :
            range_result_iterator<T>
        { };

        template< class Result, class T >
        Result call(T& x) const
        {
            typedef typename boost::remove_const<T>::type plain_t;
            return pstade_oven_extension::Range<plain_t>().BOOST_NESTED_TEMPLATE end<Result>(x);
        }
    };

    PSTADE_CONSTANT(PSTADE_OVEN_BOOST_RANGE_END, (op_end))


    template< class T >
    struct range_size
    {
        typedef std::size_t type;
    };


#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)

    struct op_size :
        callable<op_size>
    {
        template< class Myself, class T >
        struct apply :
            range_size<T>
        { };

        template< class Result, class T >
        Result call(T const& x) const
        {
            return pstade::copy_construct<Result>(
                detail::iter_distance(PSTADE_OVEN_BOOST_RANGE_BEGIN(x), PSTADE_OVEN_BOOST_RANGE_END(x))
            );
        }
    };

    PSTADE_CONSTANT(boost_range_size, (op_size))

#endif


} } } // namespace pstade::oven::extension_detail


// Bridge macros between Oven and Boost.Range Extension


#define PSTADE_OVEN_EXTENSION_OF_TYPE(NameSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_OF_TYPE_forward_meta(PSTADE_PP_FULLNAME(NameSeq), PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_OF_TYPE_forward_meta(PSTADE_PP_FULLNAME(NameSeq), range_const_iterator) \
        PSTADE_OVEN_EXTENSION_OF_TYPE_forward_meta(PSTADE_PP_FULLNAME(NameSeq), range_size) \
    } \
    \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        PSTADE_OVEN_EXTENSION_OF_TYPE_forward(PSTADE_PP_FULLNAME(NameSeq), PSTADE_OVEN_BOOST_RANGE_BEGIN, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_OF_TYPE_forward(PSTADE_PP_FULLNAME(NameSeq), PSTADE_OVEN_BOOST_RANGE_END,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_OF_TYPE_forward_size(NameSeq) \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


    #define PSTADE_OVEN_EXTENSION_OF_TYPE_forward_meta(Fullname, Fun) \
        template< > \
        struct Fun< Fullname > : \
            ::pstade::oven::extension_detail::Fun< Fullname > \
        { }; \
        \
        template< > \
        struct Fun< Fullname const > : \
               Fun< Fullname > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_OF_TYPE_forward(Fullname, Fun, Result) \
        inline \
        ::pstade::oven::extension_detail::Result< Fullname >::type \
        Fun(Fullname& x) \
        { \
            return ::pstade::oven::extension_detail::Fun(x); \
        } \
        \
        inline \
        ::pstade::oven::extension_detail::Result< Fullname const >::type \
        Fun(Fullname const& x) \
        { \
            return ::pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


    #if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
        #define PSTADE_OVEN_EXTENSION_OF_TYPE_forward_size(NameSeq) \
            PSTADE_OVEN_EXTENSION_OF_TYPE_forward(PSTADE_PP_FULLNAME(NameSeq), boost_range_size, range_size) \
        /**/
    #else
        #define PSTADE_OVEN_EXTENSION_OF_TYPE_forward_size(NameSeq) \
        /**/
    #endif


#define PSTADE_OVEN_EXTENSION_OF_TEMPLATE(NameSeq, ParamSeqOrCount) \
    PSTADE_OVEN_EXTENSION_OF_TEMPLATE_aux(NameSeq, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount)) \
/**/


#define PSTADE_OVEN_EXTENSION_OF_TEMPLATE_aux(NameSeq, ParamSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_meta(PSTADE_PP_FULLNAME(NameSeq), ParamSeq, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_meta(PSTADE_PP_FULLNAME(NameSeq), ParamSeq, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_meta(PSTADE_PP_FULLNAME(NameSeq), ParamSeq, range_size) \
    } \
    \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward(PSTADE_PP_FULLNAME(NameSeq), ParamSeq, PSTADE_OVEN_BOOST_RANGE_BEGIN, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward(PSTADE_PP_FULLNAME(NameSeq), ParamSeq, PSTADE_OVEN_BOOST_RANGE_END,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_size(NameSeq, ParamSeq) \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


    #define PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_meta(Fullname, ParamSeq, Fun) \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) > \
        struct Fun< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > > : \
            ::pstade::oven::extension_detail::Fun< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > > \
        { }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) > \
        struct Fun< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > const > : \
               Fun< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward(Fullname, ParamSeq, Fun, Result) \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) > inline \
        typename ::pstade::oven::extension_detail::Result< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > >::type \
        Fun(Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) >& x) \
        { \
            return ::pstade::oven::extension_detail::Fun(x); \
        } \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) > inline \
        typename ::pstade::oven::extension_detail::Result< Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > const >::type \
        Fun(Fullname< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) > const& x) \
        { \
            return ::pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


    #if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
        #define PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_size(NameSeq, ParamSeq) \
            PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward(PSTADE_PP_FULLNAME(NameSeq), ParamSeq, boost_range_size, range_size) \
        /**/
    #else
        #define PSTADE_OVEN_EXTENSION_OF_TEMPLATE_forward_size(NameSeq, ParamSeq) \
        /**/
    #endif


#if defined(PSTADE_OVEN_IN_BOOST)
    #define boost_oven_extension             pstade_oven_extension // Do you know a better way?
    #define BOOST_OVEN_EXTENSION_OF_TYPE     PSTADE_OVEN_EXTENSION_OF_TYPE
    #define BOOST_OVEN_EXTENSION_OF_TEMPLATE PSTADE_OVEN_EXTENSION_OF_TEMPLATE
#endif


#endif
