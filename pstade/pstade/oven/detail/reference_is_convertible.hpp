#ifndef PSTADE_OVEN_DETAIL_REFERENCE_IS_CONVERTIBLE_HPP
#define PSTADE_OVEN_DETAIL_REFERENCE_IS_CONVERTIBLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Not enough.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_reference.hpp>


namespace pstade { namespace oven { namespace detail {


template< class FromReference, class ToReference >
struct reference_is_convertible_aux :
    boost::mpl::and_<
        boost::is_convertible<FromReference, ToReference>,
        boost::mpl::or_<
            boost::mpl::not_< boost::is_reference<ToReference> >,
            boost::is_reference<FromReference>
        >
    >
{ };


template< class FromIter, class ToIter >
struct reference_is_convertible :
    reference_is_convertible_aux<
        typename boost::iterator_reference<FromIter>::type,
        typename boost::iterator_reference<ToIter>::type
    >
{ };


} } } // namespace pstade::oven::detail


#endif
