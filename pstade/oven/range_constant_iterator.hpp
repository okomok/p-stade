#ifndef PSTADE_OVEN_RANGE_CONSTANT_ITERATOR_HPP
#define PSTADE_OVEN_RANGE_CONSTANT_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/const_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace pstade { namespace oven {


template< class Range >
struct range_constant_iterator :
    boost::range_const_iterator<
        typename boost::remove_cv<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
