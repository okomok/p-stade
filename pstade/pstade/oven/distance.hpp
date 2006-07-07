#ifndef PSTADE_OVEN_DISTANCE_HPP
#define PSTADE_OVEN_DISTANCE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/range/begin.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven {


template< class Range > inline
typename boost::range_difference<Range>::type 
distance(Range const& rng)
{
    return std::distance(boost::begin(rng), boost::end(rng));
}


} } // namespace pstade::oven


#endif
