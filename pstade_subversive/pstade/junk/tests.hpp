#ifndef PSTADE_OVEN_TESTS_HPP
#define PSTADE_OVEN_TESTS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/new_iterator_test.hpp>


namespace pstade { namespace oven {


template< class Range, class Difference > inline
void forward_readable_range_test(Range const& rng, Difference i, Difference j)
{
    
    boost::forward_readable_iterator_test(boost::begin(rng), boost::end(rng));
}


} } // namespace pstade::oven


#endif
