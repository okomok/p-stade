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
#include <pstade/callable.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/singleton.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_BEGIN etc.
#include "./distance.hpp"


namespace pstade_oven_extension {


    struct range_copyable
    {
        template< class X, class From >
        X copy(From& rng)
        {
            return X(boost::begin(rng), boost::end(rng));
        }
    };

    struct range_noncopyable
    {
    private:
        template< class X, class From >
        X copy(From& rng);
    };


    template< class T, class Active = void >
    struct Range :
        range_copyable
    { };


    template< class Condition >
    struct where_ :
        boost::enable_if<Condition>
    { };

    template< bool Condition >
    struct where_c :
        boost::enable_if_c<Condition>
    { };


    using pstade::const_overloaded;


} // namespace pstade_oven_extension


namespace pstade { namespace oven { namespace extension_detail {


    template< class T >
    struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename pstade_oven_extension::Range<plain_t>::
            template associate<plain_t>::mutable_iterator type;
    };


    template< class T >
    struct range_const_iterator
    {
        typedef typename remove_cvr<T>::type plain_t;
        typedef typename pstade_oven_extension::Range<plain_t>::
            template associate<plain_t>::constant_iterator type;
    };


    template< class T >
    struct range_result_iterator :
        boost::mpl::eval_if< boost::is_const<typename boost::remove_reference<T>::type>,
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
            typedef typename boost::remove_cv<T>::type plain_t;
            return pstade_oven_extension::Range<plain_t>().template begin<Result>(x);
        }
    };

    PSTADE_SINGLETON_CONST(PSTADE_OVEN_BOOST_RANGE_BEGIN, op_begin)


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
            typedef typename boost::remove_cv<T>::type plain_t;
            return pstade_oven_extension::Range<plain_t>().template end<Result>(x);
        }
    };

    PSTADE_SINGLETON_CONST(PSTADE_OVEN_BOOST_RANGE_END, op_end)


    template< class T >
    struct range_size
    {
        typedef typename range_result_iterator<T>::type miter_t;
        typedef typename boost::iterator_difference<miter_t>::type type;
    };

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
            return oven::distance(x);
        }
    };

    PSTADE_SINGLETON_CONST(boost_range_size, op_size)


} } } // namespace pstade::oven::extension_detail


// Bridge macros between Oven and Boost.Range Extension
//

#define PSTADE_OVEN_EXTENSION_TYPE(NameSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, range_size) \
    } \
    \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, PSTADE_OVEN_BOOST_RANGE_BEGIN, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, PSTADE_OVEN_BOOST_RANGE_END,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, boost_range_size,              range_size) \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


    #define PSTADE_OVEN_EXTENSION_TYPE_forward_meta(NameSeq, Fun) \
        template< > \
        struct Fun< PSTADE_PP_FULLNAME(NameSeq) > : \
            pstade::oven::extension_detail::Fun< PSTADE_PP_FULLNAME(NameSeq) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_PP_FULLNAME(NameSeq) & > : \
            Fun< PSTADE_PP_FULLNAME(NameSeq) > \
        { }; \
        \
        template< > \
        struct Fun< PSTADE_PP_FULLNAME(NameSeq) const > : \
            Fun< PSTADE_PP_FULLNAME(NameSeq) > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TYPE_forward(NameSeq, Fun, Result) \
        inline \
        pstade::oven::extension_detail::Result< PSTADE_PP_FULLNAME(NameSeq) >::type \
        Fun(PSTADE_PP_FULLNAME(NameSeq)& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
        \
        inline \
        pstade::oven::extension_detail::Result< PSTADE_PP_FULLNAME(NameSeq) const >::type \
        Fun(PSTADE_PP_FULLNAME(NameSeq) const& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


#define PSTADE_OVEN_EXTENSION_TEMPLATE(NameSeq, ParamSeqOrCount) \
    PSTADE_OVEN_EXTENSION_TEMPLATE_impl( \
        NameSeq, \
        PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount) \
    ) \
/**/


#define PSTADE_OVEN_EXTENSION_TEMPLATE_impl(NameSeq, ParamSeq) \
    namespace boost { \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, range_const_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, range_size) \
    } \
    \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, PSTADE_OVEN_BOOST_RANGE_BEGIN, range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, PSTADE_OVEN_BOOST_RANGE_END,   range_result_iterator) \
        PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, boost_range_size,              range_size) \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) \
        PSTADE_PP_FULLNAME(NameSeq)< PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) > \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_forward_meta(NameSeq, ParamSeq, Fun) \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > : \
            pstade::oven::extension_detail::Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > \
        { }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) & > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > \
        { }; \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > \
        struct Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) const > : \
            Fun< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) > \
        { }; \
    /**/


    #define PSTADE_OVEN_EXTENSION_TEMPLATE_forward(NameSeq, ParamSeq, Fun, Result) \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > inline \
        typename pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) >::type \
        Fun(PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq)& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
        \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) > inline \
        typename pstade::oven::extension_detail::Result< PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) const >::type \
        Fun(PSTADE_OVEN_EXTENSION_TEMPLATE_fullname(NameSeq, ParamSeq) const& x) \
        { \
            return pstade::oven::extension_detail::Fun(x); \
        } \
    /**/


#endif
