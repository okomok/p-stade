#ifndef PSTADE_IS_NDEBUG_HPP
#define PSTADE_IS_NDEBUG_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace pstade {


template< class = void >
struct is_ndebug :
#if defined(NDEBUG) && !defined(PSTADE_IS_NDEBUG_DEBUG)
    boost::mpl::true_
#else
    boost::mpl::false_
#endif
{ };


#if 0

// 'true_' and 'false_' is cute enough?

typedef boost::mpl::true_
ndebug_tag;

typedef boost::mpl::false_
debug_tag;

#endif


} // namespace pstade


#endif
