#ifndef PSTADE_EGG_DETAIL_TUPLE_DROP_HPP
#define PSTADE_EGG_DETAIL_TUPLE_DROP_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/is_boost_tuple.hpp>
#include <pstade/enable_if.hpp>


namespace pstade { namespace egg { namespace detail {


    // tuple_drop
    //

    template<class N, class Tuple, class EnableIf = enabler>
    struct tuple_drop_impl;

    template<class N>
    struct little_tuple_drop
    {
        template<class Me, class Tuple>
        struct apply
        {
            typedef typename
                tuple_drop_impl<N, Tuple>::result_type
            type;
        };

        template<class Re, class Tuple>
        Re call(Tuple &t) const
        {
            return tuple_drop_impl<N, Tuple>()(t);
        }
    };

    template<class N, class Strategy>
    struct X_tuple_drop :
        function<little_tuple_drop<N>, Strategy>
    { };

    template<int N, class Strategy>
    struct X_tuple_drop_c :
        X_tuple_drop<boost::mpl::int_<N>, Strategy>
    { };


    // boost::tuple
    //

    // drop n xs | n <= 0  = xs
    // drop _ []           = []
    // drop n (_:xs)       = drop (n-1) xs

    template<int N, class Tuple>
    struct tuple_drop_aux
    {
        typedef typename
            affect_const<Tuple, typename Tuple::tail_type>::type
        tail_t;

        typedef typename
            tuple_drop_aux<N-1, tail_t>::result_type
        result_type;

        result_type operator()(Tuple &t) const
        {
            return tuple_drop_aux<N-1, tail_t>()(t.get_tail());
        }
    };

    template<class Tuple>
    struct tuple_drop_aux<0, Tuple>
    {
        typedef Tuple &result_type;

        result_type operator()(Tuple &t) const
        {
            return t;
        }
    };

    // needed cuz t.get_tail() doesn't return reference when t is one element tuple.
    template< >
    struct tuple_drop_aux<0, boost::tuples::null_type>
    {
        typedef boost::tuples::null_type result_type;

        result_type operator()(boost::tuples::null_type t) const
        {
            return t;
        }
    };

    template< >
    struct tuple_drop_aux<0, boost::tuples::null_type const> :
        tuple_drop_aux<0, boost::tuples::null_type>
    { };


    template<class N, class Tuple>
    struct tuple_drop_impl<N, Tuple,
        typename enable_if< apple::is_boost_tuple<Tuple> >::type>
    {
        typedef typename
            tuple_drop_aux<N::value, Tuple>::result_type
        result_type;

        result_type operator()(Tuple &t) const
        {
            return tuple_drop_aux<N::value, Tuple>()(t);
        }
    };


} } } // namespace pstade::egg::detail


#endif
