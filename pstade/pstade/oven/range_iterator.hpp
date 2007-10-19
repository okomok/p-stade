#ifndef PSTADE_OVEN_RANGE_ITERATOR_HPP
#define PSTADE_OVEN_RANGE_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_RESULT_ITERATOR


namespace pstade { namespace oven {


template< class Range >
struct range_iterator :
    boost::PSTADE_OVEN_BOOST_RANGE_RESULT_ITERATOR<Range>
{ };


} } // namespace pstade::oven


#endif
