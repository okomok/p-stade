#ifndef PSTADE_OVEN_DETAIL_HAS_POSITION_HPP
#define PSTADE_OVEN_DETAIL_HAS_POSITION_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/include/classic_position_iterator_fwd.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>


namespace pstade { namespace oven { namespace detail {


template< class X >
struct is_position_iterator :
    boost::mpl::false_
{ };

template< class F, class P, class S >
struct is_position_iterator< boost::spirit::classic::position_iterator<F, P, S> > :
    boost::mpl::true_
{ };

template< class F, class P >
struct is_position_iterator< boost::spirit::classic::position_iterator2<F, P> > :
    boost::mpl::true_
{ };


template< class PositionIter, class Position >
struct has_position_aux :
    boost::is_same<typename PositionIter::position_t, Position>
{ };

template< class X, class Position >
struct has_position :
    boost::mpl::and_<
        is_position_iterator<X>,
        has_position_aux<X, Position>
    >
{ };


} } } // namespace pstade::oven::detail


#endif
