#ifndef PSTADE_OVEN_RANGE_BASE_HPP
#define PSTADE_OVEN_RANGE_BASE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_cvr.hpp>


namespace pstade { namespace oven {


template< class Range, class = void >
struct range_base_impl
{
    typedef typename Range::pstade_oven_range_base_type type;
};


template< class Range >
struct range_base :
    range_base_impl<
        typename remove_cvr<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
