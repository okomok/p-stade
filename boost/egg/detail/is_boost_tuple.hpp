#ifndef PSTADE_APPLE_IS_BOOST_TUPLE_HPP
#define PSTADE_APPLE_IS_BOOST_TUPLE_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/detail/boost_tuple_fwd.hpp>


namespace boost { namespace egg { namespace details {


    template<class X>
    struct is_boost_tuple_aux :
        mpl::false_
    { };


    template<BOOST_PP_ENUM_PARAMS(BOOST_EGG_BOOST_TUPLE_MAX_SIZE, class T)>
    struct is_boost_tuple_aux< tuples::tuple<BOOST_PP_ENUM_PARAMS(BOOST_EGG_BOOST_TUPLE_MAX_SIZE, T)> > :
        mpl::true_
    { };

    template<class HT, class TT>
    struct is_boost_tuple_aux< tuples::cons<HT, TT> > :
        mpl::true_
    { };

    template< >
    struct is_boost_tuple_aux< tuples::null_type > :
        mpl::true_
    { };


    template< class T >
    struct is_boost_tuple :
        is_boost_tuple_aux<typename remove_cv<T>::type>
    { };


} } } // namespace boost::egg::details


#endif
