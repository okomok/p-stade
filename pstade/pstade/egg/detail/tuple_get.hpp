#ifndef PSTADE_EGG_DETAIL_TUPLE_GET_HPP
#define PSTADE_EGG_DETAIL_TUPLE_GET_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/apple/is_pair.hpp>
#include <pstade/enable_if.hpp>
#include "./tuple_element.hpp"


namespace pstade { namespace egg { namespace detail {


    // shortcut; std::pair not supported
    //

    template<int N, class Tuple>
    struct result_of_tuple_get :
        affect<
            Tuple&,
            typename tuple_element<N, Tuple>::type
        >
    { };


    // tuple_get
    //

    template<class N, class Tuple, class EnableIf = enabler>
    struct tuple_get_impl;

    template<class N>
    struct little_tuple_get
    {
        template<class Me, class Tuple>
        struct apply
        {
            typedef typename
                tuple_get_impl<N, Tuple>::result_type
            type;
        };

        template<class Re, class Tuple>
        Re call(Tuple& t) const
        {
            return tuple_get_impl<N, Tuple>()(t);
        }
    };

    template<class N>
    struct X_tuple_get :
        function<little_tuple_get<N>, by_perfect>
    { };

    template<int N>
    struct X_tuple_get_c :
        X_tuple_get< boost::mpl::int_<N> >
    { };


    // boost::tuple
    //

    template<class N, class Tuple>
    struct tuple_get_impl<N, Tuple, typename enable_if< apple::is_boost_tuple<Tuple> >::type>
    {
        typedef typename
            result_of_tuple_get<N::value, Tuple>::type
        result_type;

        result_type operator()(Tuple& t) const
        {
            return boost::tuples::get<N::value>(t);
        }
    };


    // std::pair
    //

    template<int N, class Pair>
    struct pair_get_aux;

    template<class Pair>
    struct pair_get_aux<0, Pair>
    {
        typedef typename
            affect<Pair&, typename Pair::first_type>::type
        result_type;

        result_type operator()(Pair& p) const
        {
            return p.first;
        }
    };

    template<class Pair>
    struct pair_get_aux<1, Pair>
    {
        typedef typename
            affect<Pair&, typename Pair::second_type>::type
        result_type;

        result_type operator()(Pair& p) const
        {
            return p.second;
        }
    };

    template<class N, class Tuple>
    struct tuple_get_impl<N, Tuple, typename enable_if< apple::is_pair<Tuple> >::type> :
        pair_get_aux<N::value, Tuple>
    { };


} } } // namespace pstade::egg::detail


#endif
