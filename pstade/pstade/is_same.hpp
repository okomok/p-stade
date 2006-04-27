#ifndef PSTADE_IS_SAME_HPP
#define PSTADE_IS_SAME_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>


namespace pstade {


template< class T > inline
bool is_same(T& x, T& y)
{
    return boost::addressof(x) == boost::addressof(y);
}


} // namespace pstade


#endif
