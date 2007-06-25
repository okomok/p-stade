#ifndef PSTADE_OVEN_DETAIL_IS_REFERENCE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_IS_REFERENCE_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Value, class Reference >
struct is_reference_iterator_aux :
    boost::mpl::or_<
        boost::is_same<Reference, Value&>,
        boost::is_same<Reference, Value const&>,
        boost::is_same<Reference, Value const volatile&>
    >
{ };


template< class Iterator >
struct is_reference_iterator :
    is_reference_iterator_aux<
        typename boost::iterator_value<Iterator>::type,
        typename boost::iterator_reference<Iterator>::type
    >
{ };


} } } // namespace pstade::oven::detail


#endif
