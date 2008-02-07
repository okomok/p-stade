#ifndef PSTADE_MPL_BOOST_TUPLE_HPP
#define PSTADE_MPL_BOOST_TUPLE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] boost::mpl::list iterator


#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/boost_tuple_config.hpp>


struct ERROR_PSTADE_MPL_BOOST_TUPLE_NOT_BIDIRECTIONAL;

template<class Iterator>
struct ERROR_PSTADE_MPL_BOOST_TUPLE_OUT_OF_RANGE;

template<class Iterator>
struct ERROR_PSTADE_MPL_BOOST_TUPLE_DANGLING;


namespace pstade { namespace mpl_boost_tuple {


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
        typedef ERROR_PSTADE_MPL_BOOST_TUPLE_NOT_BIDIRECTIONAL prior;
    };

    template< >
    struct iterator< tuples::null_type >
    {
        typedef boost::mpl::forward_iterator_tag category;
        typedef ERROR_PSTADE_MPL_BOOST_TUPLE_DANGLING<iterator> type;
        typedef ERROR_PSTADE_MPL_BOOST_TUPLE_OUT_OF_RANGE<iterator> next;
        typedef ERROR_PSTADE_MPL_BOOST_TUPLE_NOT_BIDIRECTIONAL prior;
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


} } // namespace pstade::mpl_boost_tuple


namespace boost { namespace mpl {


    template<BOOST_PP_ENUM_PARAMS(PSTADE_BOOST_TUPLE_MAX_SIZE, class T)>
    struct sequence_tag< tuples::tuple<BOOST_PP_ENUM_PARAMS(PSTADE_BOOST_TUPLE_MAX_SIZE, T)> >
    {
        typedef pstade::mpl_boost_tuple::tag type;
    };

    template<class HT, class TT>
    struct sequence_tag< tuples::cons<HT, TT> >
    {
        typedef pstade::mpl_boost_tuple::tag type;
    };
    
    template< >
    struct sequence_tag< tuples::null_type >
    {
        typedef pstade::mpl_boost_tuple::tag type;
    };


    template< >
    struct begin_impl<pstade::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef
                pstade::mpl_boost_tuple::iterator<
                    typename pstade::mpl_boost_tuple::recons<Tuple>::type
                >
            type;
        };
    };

    template< >
    struct end_impl<pstade::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef
                pstade::mpl_boost_tuple::iterator<tuples::null_type>
            type;
        };
    };

    template< >
    struct clear_impl<pstade::mpl_boost_tuple::tag>
    {
        template<class Tuple>
        struct apply
        {
            typedef tuples::null_type type;
        };
    };

    template< >
    struct push_front_impl<pstade::mpl_boost_tuple::tag>
    {
        template<class Tuple, class T>
        struct apply
        {
            typedef
                tuples::cons<T, typename pstade::mpl_boost_tuple::recons<Tuple>::type>
            type;
        };
    };

    template< >
    struct pop_front_impl<pstade::mpl_boost_tuple::tag>
    {
        template<class Tuple, class T>
        struct apply
        {
            typedef typename Tuple::tail_type type;
        };
    };


} } // namespace boost::mpl


#endif
