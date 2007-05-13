#ifndef PSTADE_OVEN_RANGE_MUTABLE_ITERATOR_HPP
#define PSTADE_OVEN_RANGE_MUTABLE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_cvr.hpp>
#include "./detail/config.hpp" // BOOST_RANGE_MUTABLE_ITERATOR


namespace pstade { namespace oven {


template< class Range >
struct range_mutable_iterator :
    PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<
        typename remove_cvr<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
