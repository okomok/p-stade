#ifndef PSTADE_OVEN_RANGE_POINTER_HPP
#define PSTADE_OVEN_RANGE_POINTER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include "./detail/ref_to_ptr.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"


namespace pstade { namespace oven {


// may return a proxy type.
template< class Range >
struct range_pointer :
    boost::iterator_pointer<
        typename range_iterator<Range>::type
    >
{ };


// returns a pointer type to (possibly const) value_type.
template< class Range >
struct range_lvalue_pointer :
    detail::ref_to_ptr<
        typename range_reference<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
