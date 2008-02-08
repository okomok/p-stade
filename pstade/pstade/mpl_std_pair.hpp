#ifndef PSTADE_MPL_STD_PAIR_HPP
#define PSTADE_MPL_STD_PAIR_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <utility> // pair
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/size_fwd.hpp>


template<class Iterator>
struct ERROR_PSTADE_MPL_STD_PAIR_OUT_OF_RANGE;

template<class Iterator>
struct ERROR_PSTADE_MPL_STD_PAIR_DANGLING;


namespace pstade { namespace mpl_std_pair {


    struct tag;


    template<class Pair, int N>
    struct iterator;

    template<class Pair>
    struct iterator<Pair, 0>
    {
        typedef boost::mpl::random_access_iterator_tag category;
        typedef typename Pair::first_type type;
        typedef iterator<Pair, 1> next;
        typedef ERROR_PSTADE_MPL_STD_PAIR_OUT_OF_RANGE<iterator> prior;
    };

    template<class Pair>
    struct iterator<Pair, 1>
    {
        typedef boost::mpl::random_access_iterator_tag category;
        typedef typename Pair::second_type type;
        typedef iterator<Pair, 2> next;
        typedef iterator<Pair, 0> prior;
    };

    template<class Pair>
    struct iterator<Pair, 2>
    {
        typedef boost::mpl::random_access_iterator_tag category;
        typedef ERROR_PSTADE_MPL_STD_PAIR_DANGLING<iterator> type;
        typedef ERROR_PSTADE_MPL_STD_PAIR_OUT_OF_RANGE<iterator> next;
        typedef iterator<Pair, 1> prior;
    };


    template<class Pair, class N>
    struct iterator_aux :
        iterator<Pair, N::value>
    { };


    template<class Pair, int N>
    struct at;

    template<class Pair>
    struct at<Pair, 0>
    {
        typedef typename Pair::first_type type;
    };

    template<class Pair>
    struct at<Pair, 1>
    {
        typedef typename Pair::second_type type;
    };


} } // namespace pstade::mpl_std_pair


namespace boost { namespace mpl {


    template<class Pair, class Pos, class N>
    struct advance<pstade::mpl_std_pair::iterator_aux<Pair, Pos>, N>
    {
        typedef
            pstade::mpl_std_pair::iterator_aux<Pair, typename plus<Pos, N>::type>
        type;
    };

    template<class Pair, class Pos1, class Pos2>
    struct distance<
        pstade::mpl_std_pair::iterator_aux<Pair, Pos1>,
        pstade::mpl_std_pair::iterator_aux<Pair, Pos2>
    > :
        minus<Pos2, Pos1>
    { };


    template<class T, class U>
    struct sequence_tag< std::pair<T, U> >
    {
        typedef pstade::mpl_std_pair::tag type;
    };


    template< >
    struct begin_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair>
        struct apply
        {
            typedef pstade::mpl_std_pair::iterator<Pair, 0> type;
        };
    };

    template< >
    struct end_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair>
        struct apply
        {
            typedef pstade::mpl_std_pair::iterator<Pair, 2> type;
        };
    };

    template< >
    struct at_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair, class N>
        struct apply :
            pstade::mpl_std_pair::at<Pair, N::value>
        { };
    };


    // optimizations
    //

    template< >
    struct empty_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair>
        struct apply :
            false_
        { };
    };

    template< >
    struct front_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair>
        struct apply
        {
            typedef typename Pair::first_type type;
        };
    };

    template< >
    struct back_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair>
        struct apply
        {
            typedef typename Pair::second_type type;
        };
    };

    template< >
    struct size_impl<pstade::mpl_std_pair::tag>
    {
        template<class Pair>
        struct apply :
            int_<2>
        { };
    };


} } // namespace boost::mpl


#endif
