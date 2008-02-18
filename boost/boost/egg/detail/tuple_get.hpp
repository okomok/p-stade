#ifndef BOOST_EGG_DETAIL_TUPLE_GET_HPP
#define BOOST_EGG_DETAIL_TUPLE_GET_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp> // get
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/is_boost_tuple.hpp>
#include <boost/egg/detail/result_of_tuple_get.hpp>


namespace boost { namespace egg { namespace details {


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
        Re call(Tuple &t) const
        {
            return tuple_get_impl<N, Tuple>()(t);
        }
    };

    template<class N>
    struct X_tuple_get :
        function<little_tuple_get<N>, by_perfect>
    { };


    // boost::tuple
    //

    template<class N, class Tuple>
    struct tuple_get_impl<N, Tuple,
        typename enable_if< is_boost_tuple<Tuple> >::type
    >
    {
        typedef typename
            result_of_tuple_get<N::value, Tuple>::type
        result_type;

        result_type operator()(Tuple &t) const
        {
            return tuples::get<N::value>(t);
        }
    };


} } } // namespace boost::egg::details


#endif
