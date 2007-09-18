#ifndef PSTADE_APPLE_IS_BOOST_TUPLE_HPP
#define PSTADE_APPLE_IS_BOOST_TUPLE_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/tuple/tuple.hpp>


namespace pstade { namespace apple {


template<class X>
struct is_boost_tuple :
    boost::mpl::false_
{ };


template<BOOST_PP_ENUM_PARAMS(10, class T)>
struct is_boost_tuple< boost::tuples::tuple<BOOST_PP_ENUM_PARAMS(10, T)> > :
    boost::mpl::true_
{ };

template<class Head, class Tail>
struct is_boost_tuple< boost::tuples::cons<Head, Tail> > :
    boost::mpl::true_
{ };

template< >
struct is_boost_tuple< boost::tuples::null_type > :
    boost::mpl::true_
{ };


} } // namespace pstade::apple


#endif
