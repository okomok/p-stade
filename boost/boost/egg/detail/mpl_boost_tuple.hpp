#ifndef BOOST_EGG_DETAIL_MPL_BOOST_TUPLE_HPP
#define BOOST_EGG_DETAIL_MPL_BOOST_TUPLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] boost::mpl::list iterator


#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/size_fwd.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/egg/detail/boost_tuple_fwd.hpp>


struct ERROR_BOOST_EGG_MPL_BOOST_TUPLE_NOT_BIDIRECTIONAL;

template<class Iterator>
struct ERROR_BOOST_EGG_MPL_BOOST_TUPLE_OUT_OF_RANGE;

template<class Iterator>
struct ERROR_BOOST_EGG_MPL_BOOST_TUPLE_DANGLING;


namespace boost { namespace egg { namespace mpl_boost_tuple {


    namespace tuples = boost::tuples;


    struct tag;


    template<class Tuple>
    struct iterator;

    template<class HT, class TT>
    struct iterator< tuples::cons<HT, TT> >
    {
        typedef boost::mpl::forward_iterator_tag category;
        typedef HT type;
        typedef iterator<TT> next;
        typedef ERROR_BOOST_EGG_MPL_BOOST_TUPLE_NOT_BIDIRECTIONAL prior;
    };

    template< >
    struct iterator< tuples::null_type >
    {
        typedef boost::mpl::forward_iterator_tag category;
        typedef ERROR_BOOST_EGG_MPL_BOOST_TUPLE_DANGLING<iterator> type;
        typedef ERROR_BOOST_EGG_MPL_BOOST_TUPLE_OUT_OF_RANGE<iterator> next;
        typedef ERROR_BOOST_EGG_MPL_BOOST_TUPLE_NOT_BIDIRECTIONAL prior;
    };


    // reconstruction for `tuple<T1,T2,...>` form
    template<class Tuple>
    struct recons
    {
        typedef tuples::cons<typename Tuple::head_type, typename Tuple::tail_type> type;
    };

    template< >
    struct recons< tuples::tuple<> >
    {
        typedef tuples::null_type type;
    };

    template<class HT, class TT>
    struct recons< tuples::cons<HT, TT> >
    {
        typedef tuples::cons<HT, TT> type;
    };

    template< >
    struct recons< tuples::null_type >
    {
        typedef tuples::null_type type;
    };


} } } // namespace boost::egg::mpl_boost_tuple


namespace boost { namespace mpl {


    template<BOOST_PP_ENUM_PARAMS(BOOST_EGG_BOOST_TUPLE_MAX_SIZE, class T)>
    struct sequence_tag< tuples::tuple<BOOST_PP_ENUM_PARAMS(BOOST_EGG_BOOST_TUPLE_MAX_SIZE, T)> >
    {
        typedef egg::mpl_boost_tuple::tag type;
    };

    template<class HT, class TT>
    struct sequence_tag< tuples::cons<HT, TT> >
    {
        typedef egg::mpl_boost_tuple::tag type;
    };
    
    template< >
    struct sequence_tag< tuples::null_type >
    {
        typedef egg::mpl_boost_tuple::tag type;
    };


    template< >
    struct begin_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef
                egg::mpl_boost_tuple::iterator<
                    typename egg::mpl_boost_tuple::recons<Tuple>::type
                >
            type;
        };
    };

    template< >
    struct end_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef
                egg::mpl_boost_tuple::iterator<tuples::null_type>
            type;
        };
    };

    template< >
    struct clear_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef tuples::null_type type;
        };
    };

    template< >
    struct push_front_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple, class T>
        struct apply
        {
            typedef
                tuples::cons<T, typename egg::mpl_boost_tuple::recons<Tuple>::type>
            type;
        };
    };

    template< >
    struct pop_front_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple, class T>
        struct apply
        {
            typedef typename Tuple::tail_type type;
        };
    };


    // optimizations
    //

    template< >
    struct at_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple, class N>
        struct apply :
            tuples::element<N::value, Tuple>
        { };

        template<class Tuple, class N>
        struct apply<Tuple const, N>;
    };

    template< >
    struct front_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef typename Tuple::head_type type;
        };
    };

    template< >
    struct size_impl<egg::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply :
            int_<tuples::length<Tuple>::value>
        { };
    };



} } // namespace boost::mpl


#endif
