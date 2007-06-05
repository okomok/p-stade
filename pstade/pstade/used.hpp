#ifndef PSTADE_USED_HPP
#define PSTADE_USED_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/unused.hpp>


namespace pstade {


template < class T > inline
void used(T const& x)
{
    // Give me the portable implementation!
    void const * volatile p = boost::addressof(x);
    pstade::unused(p);
}


} // namespace pstade


#endif
