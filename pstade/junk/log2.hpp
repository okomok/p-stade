#ifndef PSTADE_OVEN_DETAIL_LOG2_HPP
#define PSTADE_OVEN_DETAIL_LOG2_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cmath> // log2
#include <boost/assert.hpp>
#include <pstade/egg/copy.hpp>


namespace pstade { namespace oven { namespace detail {


inline
int log2(int n)
{
    BOOST_ASSERT(n > 0);
    return egg::copy<int>( std::log2(egg::copy<double>(n)) );
}


} } } // namespace pstade::oven::detail


#endif
