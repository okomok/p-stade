#ifndef PSTADE_OVEN_COPIES_HPP
#define PSTADE_OVEN_COPIES_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // copy
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/oven/distance.hpp>


namespace pstade { namespace oven {


template< class RangeIn, class RangeOut > inline
typename boost::range_result_iterator<RangeOut>::type
copies(const RangeIn& in, RangeOut& out)
{
    BOOST_STATIC_ASSERT(!boost::is_const<RangeOut>::value);
    BOOST_ASSERT(oven::distance(in) <= oven::distance(out) && "out of range");

    return std::copy(boost::begin(in), boost::end(in), boost::begin(out));
}


} } // namespace pstade::oven


#endif
